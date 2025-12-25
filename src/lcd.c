#include "lcd.h"
#include <memory.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#if LCD_BUS == LCD_BUS_SPI
#include "driver/spi_master.h"
#endif
#if LCD_BUS == LCD_BUS_I2C
#ifndef LEGACY_I2C
#include "driver/i2c_master.h"
#else
#include "driver/i2c.h"
#endif
#endif
#ifdef LCD_PHY_PWR_LDO_CHAN
#include "esp_ldo_regulator.h"
#endif
#if LCD_BUS == LCD_BUS_MIPI
#include "esp_dma_utils.h"
#include "esp_lcd_mipi_dsi.h"
#endif

static const char* TAG = "lcd";
static esp_lcd_panel_handle_t panel_handle = NULL;
static esp_lcd_panel_io_handle_t io_handle = NULL;
#if LCD_BUS == LCD_BUS_MIPI
static esp_ldo_channel_handle_t ldo_mipi_phy = NULL;
static esp_lcd_dsi_bus_handle_t mipi_dsi_bus = NULL;
#endif
static size_t draw_buffer_size = 0;
static void* draw_buffer = NULL;
#ifdef LCD_DMA
static void* draw_buffer2 = NULL;
#endif
#ifdef LCD_PIN_NUM_VSYNC
static volatile bool is_vsync = 0;
#endif
void lcd_flush(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, void *bitmap)
{
    if(panel_handle==NULL) {
        ESP_LOGE(TAG,"lcd_flush() was invoked but lcd_init() was never called.");
        return;
    }
    // pass the draw buffer to the driver
    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, x1, y1, x2 + 1, y2 + 1, bitmap));
#ifndef LCD_DMA
    lcd_flush_complete();
#endif
}

#if LCD_BUS == LCD_BUS_RGB
// LCD Panel API calls this
static IRAM_ATTR bool lcd_on_flush_complete(esp_lcd_panel_handle_t panel, const esp_lcd_rgb_panel_event_data_t *edata, void *user_ctx) {
    is_vsync = 0;
    // let the display know the flush has finished
    lcd_flush_complete();
    return true;
}
// LCD Panel API calls this
static IRAM_ATTR bool lcd_vsync(esp_lcd_panel_handle_t panel, const esp_lcd_rgb_panel_event_data_t *edata, void *user_ctx) {
    is_vsync=1;
    return true;
}
#endif
#if LCD_BUS==LCD_BUS_SPI || LCD_BUS==LCD_BUS_I2C || LCD_BUS==LCD_BUS_I8080
static IRAM_ATTR bool lcd_on_flush_complete(esp_lcd_panel_io_handle_t lcd_io, esp_lcd_panel_io_event_data_t* edata, void* user_ctx) {
    // let the display know the flush has finished
    lcd_flush_complete();
    return true;
}
#endif
#if LCD_BUS == LCD_BUS_MIPI
static IRAM_ATTR bool lcd_on_flush_complete(esp_lcd_panel_handle_t panel, esp_lcd_dpi_panel_event_data_t *edata, void *user_ctx) {
    // let the display know the flush has finished
    lcd_flush_complete();
    return true;
}
#endif
void lcd_init(void) {
    if(panel_handle!=NULL) {
        ESP_LOGW(TAG,"lcd_init() was already called");
        return; // already initialized
    }
#ifdef LCD_PIN_NUM_BCKL
#if LCD_PIN_NUM_BCKL >= 0
    gpio_config_t bk_gpio_config;
    memset(&bk_gpio_config,0,sizeof(gpio_config_t));
    bk_gpio_config.mode = GPIO_MODE_OUTPUT;
    bk_gpio_config.pin_bit_mask = 1ULL << LCD_PIN_NUM_BCKL;
    ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));
    gpio_set_level((gpio_num_t)LCD_PIN_NUM_BCKL, LCD_BCKL_OFF_LEVEL);
#endif
#endif
    // Turn on the power for MIPI DSI PHY, so it can go from "No Power" state to "Shutdown" state
#ifdef LCD_PHY_PWR_LDO_CHAN
    esp_ldo_channel_config_t ldo_mipi_phy_config = {
        .chan_id = LCD_MIPI_DSI_PHY_PWR_LDO_CHAN,
        .voltage_mv = LCD_MIPI_DSI_PHY_PWR_LDO_VOLTAGE_MV,
    };
    ESP_ERROR_CHECK(esp_ldo_acquire_channel(&ldo_mipi_phy_config, &ldo_mipi_phy));
#endif

#if LCD_BUS == LCD_RGB
    esp_lcd_rgb_panel_config_t panel_config;
    memset(&panel_config,0,sizeof(esp_lcd_rgb_panel_config_t));
    panel_config.data_width = 16; // RGB565 in parallel mode, thus 16bit in width
    //panel_config.dma_burst_size = 64;
    panel_config.num_fbs = 1,
    panel_config.clk_src = LCD_CLK_SRC_DEFAULT,
    panel_config.disp_gpio_num = -1,
    panel_config.pclk_gpio_num = LCD_PIN_NUM_CLK,
    panel_config.vsync_gpio_num = LCD_PIN_NUM_VSYNC,
    panel_config.hsync_gpio_num = LCD_PIN_NUM_HSYNC,
    panel_config.de_gpio_num = LCD_PIN_NUM_DE,
#if LCD_BIT_DEPTH == 8
    panel_config.data_gpio_nums[8]=LCD_PIN_NUM_D08;
    panel_config.data_gpio_nums[9]=LCD_PIN_NUM_D09;
    panel_config.data_gpio_nums[10]=LCD_PIN_NUM_D10;
    panel_config.data_gpio_nums[11]=LCD_PIN_NUM_D11;
    panel_config.data_gpio_nums[12]=LCD_PIN_NUM_D12;
    panel_config.data_gpio_nums[13]=LCD_PIN_NUM_D13;
    panel_config.data_gpio_nums[14]=LCD_PIN_NUM_D14;
    panel_config.data_gpio_nums[15]=LCD_PIN_NUM_D15;
#elif !defined(LCD_SWAP_COLOR_BYTES) || LCD_SWAP_COLOR_BYTES == false
    panel_config.data_gpio_nums[0]=LCD_PIN_NUM_D00;
    panel_config.data_gpio_nums[1]=LCD_PIN_NUM_D01;
    panel_config.data_gpio_nums[2]=LCD_PIN_NUM_D02;
    panel_config.data_gpio_nums[3]=LCD_PIN_NUM_D03;
    panel_config.data_gpio_nums[4]=LCD_PIN_NUM_D04;
    panel_config.data_gpio_nums[5]=LCD_PIN_NUM_D05;
    panel_config.data_gpio_nums[6]=LCD_PIN_NUM_D06;
    panel_config.data_gpio_nums[7]=LCD_PIN_NUM_D07;
    panel_config.data_gpio_nums[8]=LCD_PIN_NUM_D08;
    panel_config.data_gpio_nums[9]=LCD_PIN_NUM_D09;
    panel_config.data_gpio_nums[10]=LCD_PIN_NUM_D10;
    panel_config.data_gpio_nums[11]=LCD_PIN_NUM_D11;
    panel_config.data_gpio_nums[12]=LCD_PIN_NUM_D12;
    panel_config.data_gpio_nums[13]=LCD_PIN_NUM_D13;
    panel_config.data_gpio_nums[14]=LCD_PIN_NUM_D14;
    panel_config.data_gpio_nums[15]=LCD_PIN_NUM_D15;
#else
    panel_config.data_gpio_nums[0]=LCD_PIN_NUM_D08;
    panel_config.data_gpio_nums[1]=LCD_PIN_NUM_D09;
    panel_config.data_gpio_nums[2]=LCD_PIN_NUM_D10;
    panel_config.data_gpio_nums[3]=LCD_PIN_NUM_D11;
    panel_config.data_gpio_nums[4]=LCD_PIN_NUM_D12;
    panel_config.data_gpio_nums[5]=LCD_PIN_NUM_D13;
    panel_config.data_gpio_nums[6]=LCD_PIN_NUM_D14;
    panel_config.data_gpio_nums[7]=LCD_PIN_NUM_D15;
    panel_config.data_gpio_nums[8]=LCD_PIN_NUM_D00;
    panel_config.data_gpio_nums[9]=LCD_PIN_NUM_D01;
    panel_config.data_gpio_nums[10]=LCD_PIN_NUM_D02;
    panel_config.data_gpio_nums[11]=LCD_PIN_NUM_D03;
    panel_config.data_gpio_nums[12]=LCD_PIN_NUM_D04;
    panel_config.data_gpio_nums[13]=LCD_PIN_NUM_D05;
    panel_config.data_gpio_nums[14]=LCD_PIN_NUM_D06;
    panel_config.data_gpio_nums[15]=LCD_PIN_NUM_D07;
#endif
    memset(&panel_config.timings,0,sizeof(esp_lcd_rgb_timing_t));
    panel_config.timings.pclk_hz = LCD_PIXEL_CLOCK_HZ;
    panel_config.timings.h_res = LCD_HRES;
    panel_config.timings.v_res = LCD_VRES;
    panel_config.timings.hsync_back_porch = LCD_HSYNC_BACK_PORCH;
    panel_config.timings.hsync_front_porch = LCD_HSYNC_FRONT_PORCH;
    panel_config.timings.hsync_pulse_width = LCD_HSYNC_PULSE_WIDTH;
    panel_config.timings.vsync_back_porch = LCD_VSYNC_BACK_PORCH;
    panel_config.timings.vsync_front_porch = LCD_VSYNC_FRONT_PORCH;
    panel_config.timings.vsync_pulse_width = LCD_VSYNC_PULSE_WIDTH;
    panel_config.timings.flags.pclk_active_neg = true;
    panel_config.timings.flags.hsync_idle_low = false;
    panel_config.timings.flags.pclk_idle_high = LCD_CLK_IDLE_HIGH;
    panel_config.timings.flags.de_idle_high = LCD_DE_IDLE_HIGH;
    panel_config.timings.flags.vsync_idle_low = false;
    panel_config.flags.bb_invalidate_cache = true;
    panel_config.flags.disp_active_low = false;
    panel_config.flags.double_fb = false;
    panel_config.flags.no_fb = false;
    panel_config.flags.refresh_on_demand = false;
    panel_config.flags.fb_in_psram = true; // allocate frame buffer in PSRAM
    //panel_config.sram_trans_align = 4;
    //panel_config.psram_trans_align = 64;
    panel_config.num_fbs = 2;
    panel_config.bounce_buffer_size_px = LCD_HRES*(LCD_VRES/LCD_DIVISOR);
    ESP_ERROR_CHECK(esp_lcd_new_rgb_panel(&panel_config, &panel_handle));
    esp_lcd_rgb_panel_event_callbacks_t cbs;
    memset(&cbs,0,sizeof(cbs));
    cbs.on_color_trans_done = lcd_flush_complete;
    cbs.on_vsync = lcd_vsync;
    esp_lcd_rgb_panel_register_event_callbacks(panel_handle,&cbs,NULL);
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
#endif
#if LCD_BUS == LCD_BUS_SPI
    spi_bus_config_t spi_cfg;
    memset(&spi_cfg,0,sizeof(spi_cfg));
    uint32_t spi_sz = LCD_TRANSFER_SIZE+8;
    if(spi_sz>32*1024) {
        ESP_LOGW(TAG,"SPI transfer size is limited to 32KB, but draw buffer demands more. Increase the LCD_DIVISOR");
        spi_sz = 32*1024;
    }
    spi_cfg.max_transfer_sz = spi_sz;
    spi_cfg.mosi_io_num = LCD_PIN_NUM_MOSI;
    spi_cfg.sclk_io_num = LCD_PIN_NUM_CLK;
#ifdef LCD_PIN_NUM_MISO
    spi_cfg.miso_io_num = LCD_PIN_NUM_MISO;
#else    
    spi_cfg.miso_io_num = -1;
#endif
    spi_cfg.quadwp_io_num = -1;
    spi_cfg.quadhd_io_num = -1;
    ESP_ERROR_CHECK(spi_bus_initialize((spi_host_device_t)LCD_SPI_HOST,&spi_cfg,SPI_DMA_CH_AUTO));
    esp_lcd_panel_io_spi_config_t lcd_spi_cfg;
    memset(&lcd_spi_cfg,0,sizeof(lcd_spi_cfg));
    lcd_spi_cfg.cs_gpio_num = LCD_PIN_NUM_CS;
    lcd_spi_cfg.dc_gpio_num = LCD_PIN_NUM_DC;
    lcd_spi_cfg.lcd_cmd_bits = LCD_CMD_BITS;
    lcd_spi_cfg.lcd_param_bits = LCD_PARAM_BITS;        
#ifdef LCD_PIXEL_CLOCK_HZ
    lcd_spi_cfg.pclk_hz = LCD_PIXEL_CLOCK_HZ;
#else
    lcd_spi_cfg.pclk_hz = 20 * 1000 * 1000;
#endif
    lcd_spi_cfg.trans_queue_depth = 10;
    lcd_spi_cfg.on_color_trans_done = lcd_on_flush_complete;
    esp_lcd_panel_io_handle_t io_handle = NULL;
#ifdef LCD_SPI_MODE
    lcd_spi_cfg.spi_mode = LCD_SPI_MODE;
#else
    lcd_spi_cfg.spi_mode = 0;
#endif
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_SPI_HOST, &lcd_spi_cfg, &io_handle));
#endif
#if LCD_BUS == LCD_BUS_I2C
#ifndef LEGACY_I2C
    i2c_master_bus_config_t i2c_cfg;
    i2c_master_bus_handle_t i2c_bus_handle;
    memset(&i2c_cfg,0,sizeof(i2c_cfg));
    i2c_cfg.clk_source = I2C_CLK_SRC_DEFAULT;
    i2c_cfg.glitch_ignore_cnt = 7;
    i2c_cfg.i2c_port = (i2c_port_num_t)LCD_I2C_HOST;
// Doesn't actually work, which is why it's commented out.
//#ifdef LCD_DMA
    //i2c_cfg.trans_queue_depth = 10;
// #endif
    i2c_cfg.sda_io_num = (gpio_num_t)LCD_PIN_NUM_SDA;
    i2c_cfg.scl_io_num = (gpio_num_t)LCD_PIN_NUM_SCL;
    i2c_cfg.flags.enable_internal_pullup = 1;
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_cfg,&i2c_bus_handle));
#else
    i2c_config_t i2c_cfg;
    memset(&i2c_cfg,0,sizeof(i2c_cfg));
#ifdef LCD_PIXEL_CLOCK_HZ
    i2c_cfg.master.clk_speed = LCD_PIXEL_CLOCK_HZ;
#else
    i2c_cfg.master.clk_speed = 100 * 1000;
#endif
    i2c_cfg.mode = I2C_MODE_MASTER;
    i2c_cfg.sda_io_num = LCD_PIN_NUM_SDA;
    i2c_cfg.sda_pullup_en = 1;
    i2c_cfg.scl_io_num = LCD_PIN_NUM_SCL;
    i2c_cfg.scl_pullup_en = 1;
    ESP_ERROR_CHECK(i2c_driver_install((i2c_port_t)LCD_I2C_HOST,I2C_MODE_MASTER,0,0,0));
    ESP_ERROR_CHECK(i2c_param_config((i2c_port_t)LCD_I2C_HOST,&i2c_cfg));
#endif    
    esp_lcd_panel_io_i2c_config_t lcd_i2c_cfg;
    memset(&lcd_i2c_cfg,0,sizeof(lcd_i2c_cfg));
    lcd_i2c_cfg.control_phase_bytes = LCD_CONTROL_PHASE_BYTES;
    lcd_i2c_cfg.dc_bit_offset = LCD_DC_BIT_OFFSET;
    lcd_i2c_cfg.dev_addr = LCD_I2C_ADDR;
#ifdef LCD_DISABLE_CONTROL_PHASE
    lcd_i2c_cfg.flags.disable_control_phase = true;
#endif
    lcd_i2c_cfg.lcd_cmd_bits = LCD_CMD_BITS;
    lcd_i2c_cfg.lcd_param_bits = LCD_PARAM_BITS;
#ifdef LCD_DMA
    lcd_i2c_cfg.on_color_trans_done = lcd_on_flush_complete;
#else
    lcd_i2c_cfg.on_color_trans_done = NULL;
#endif
#ifndef LEGACY_I2C
#ifdef LCD_PIXEL_CLOCK_HZ
    lcd_i2c_cfg.scl_speed_hz = LCD_PIXEL_CLOCK_HZ;
#else
    lcd_i2c_cfg.scl_speed_hz = 100 * 1000;
#endif
#else
    lcd_i2c_cfg.scl_speed_hz = 0;
#endif
#ifndef LEGACY_I2C
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c_v2((i2c_master_bus_handle_t)i2c_bus_handle, &lcd_i2c_cfg, &io_handle));
#else
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c_v1((uint32_t)LCD_I2C_HOST, &lcd_i2c_cfg, &io_handle));
#endif
#endif
#if LCD_BUS == LCD_BUS_MIPI
    esp_lcd_dsi_bus_config_t dsi_bus_config = {                                                    \
        .bus_id = LCD_MIPI_BUS_ID,                                     
        .num_data_lanes = LCD_MIPI_LANES,                             
        .phy_clk_src = LCD_MIPI_CLK_SRC,     
        .lane_bit_rate_mbps = LCD_MIPI_LANE_MBPS,                      
    };
    ESP_ERROR_CHECK(esp_lcd_new_dsi_bus(&dsi_bus_config, &mipi_dsi_bus));
    
    esp_lcd_dbi_io_config_t dbi_config = {                                 
        .virtual_channel = LCD_MIPI_CHANNEL,         
        .lcd_cmd_bits = LCD_CMD_BITS,            
        .lcd_param_bits = LCD_PARAM_BITS,          
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_dbi(mipi_dsi_bus, &dbi_config, &io_handle));

    esp_lcd_dpi_panel_config_t dpi_config=// = ST7703_720_720_PANEL_60HZ_DPI_CONFIG(MIPI_DPI_PX_FORMAT);
    {   
        .virtual_channel = LCD_MIPI_CHANNEL,                                                                             
        .dpi_clk_src = MIPI_DSI_DPI_CLK_SRC_DEFAULT,     
        .dpi_clock_freq_mhz = LCD_PIXEL_CLOCK_HZ/(1000 * 1000),                        
        .pixel_format = MIPI_DPI_PX_FORMAT,         
        .num_fbs = 1,                                    
        .video_timing = {                                
            .h_size = LCD_HRES,                               
            .v_size = LCD_VRES,                               
            .hsync_pulse_width = LCD_HSYNC_PULSE_WIDTH,                     
            .hsync_back_porch = LCD_HSYNC_BACK_PORCH,                     
            .hsync_front_porch = LCD_HSYNC_FRONT_PORCH,                    
            .vsync_pulse_width = LCD_VSYNC_PULSE_WIDTH,                     
            .vsync_back_porch = LCD_VSYNC_BACK_PORCH,                      
            .vsync_front_porch = LCD_VSYNC_FRONT_PORCH,                     
        },           
#ifdef LCD_MIPI_DMA2D                                    
        .flags.use_dma2d = 1,
#endif
    };

#endif

    esp_lcd_panel_dev_config_t panel_config;
    memset(&panel_config,0,sizeof(panel_config));
#ifdef LCD_PANEL_VENDOR_CONFIG
    LCD_PANEL_VENDOR_CONFIG;
#endif
#ifdef LCD_PIN_NUM_RST
    panel_config.reset_gpio_num = LCD_PIN_NUM_RST;
#else
    panel_config.reset_gpio_num = -1;
#endif
#if LCD_COLOR_SPACE == LCD_RGB
    panel_config.rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB;
#elif LCD_COLOR_SPACE == LCD_BGR
    panel_config.rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR;
#elif LCD_COLOR_SPACE == LCD_GSC
    // seems to work
    panel_config.rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB;
#endif
#ifdef LCD_DATA_ENDIAN_LITTLE
    panel_config.data_endian = LCD_RGB_DATA_ENDIAN_LITTLE;
#else
    panel_config.data_endian = LCD_RGB_DATA_ENDIAN_BIG;
#endif
    panel_config.bits_per_pixel = LCD_BIT_DEPTH;
#ifdef LCD_PANEL_VENDOR_CONFIG
    panel_config.vendor_config = &vendor_config;
#else
    panel_config.vendor_config = NULL;
#endif

    ESP_ERROR_CHECK(LCD_PANEL(io_handle, &panel_config, &panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
#if LCD_BUS == LCD_BUS_MIPI
    esp_lcd_dpi_panel_event_callbacks_t mipi_cbs = {
        .on_color_trans_done = lcd_on_flush_complete,
    };
    ESP_ERROR_CHECK(esp_lcd_dpi_panel_register_event_callbacks(panel_handle, &mipi_cbs, NULL));
#endif

    int gap_x = 0, gap_y = 0;
#ifdef LCD_GAP_X
    gap_x = LCD_GAP_X;
#endif
#ifdef LCD_GAP_Y
    gap_y = LCD_GAP_Y;
#endif
    if(gap_x!=0 || gap_y!=0) {
        ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel_handle,gap_x,gap_y));
    }
#ifdef LCD_SWAP_XY
#if LCD_SWAP_XY
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle,true));
#endif
#endif
    bool mirror_x = false, mirror_y = false;
#ifdef LCD_MIRROR_X
#if LCD_MIRROR_X
    mirror_x = true;
#endif
#endif
#ifdef LCD_MIRROR_Y
#if LCD_MIRROR_Y
    mirror_y = true;
#endif
#endif
    if(mirror_x || mirror_y) {
        ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle,mirror_x,mirror_y));
    }
#ifdef LCD_INVERT_COLOR
#if LCD_INVERT_COLOR
    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle,true));
#endif
#endif
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
#ifdef LCD_PIN_NUM_BCKL
#if LCD_PIN_NUM_BCKL >= 0
    gpio_set_level((gpio_num_t)LCD_PIN_NUM_BCKL, LCD_BCKL_ON_LEVEL);
#endif
#endif
    uint32_t heap_caps = MALLOC_CAP_8BIT;
#ifdef LCD_TRANSFER_IN_SPIRAM
    heap_caps |= MALLOC_CAP_SPIRAM;
#else
    heap_caps |= MALLOC_CAP_INTERNAL;
#endif
    // it's recommended to allocate the draw buffer from internal memory, for better performance
    draw_buffer_size = LCD_TRANSFER_SIZE;
    draw_buffer = heap_caps_malloc(draw_buffer_size, heap_caps);
    if(draw_buffer==NULL) {
        ESP_ERROR_CHECK(ESP_ERR_NO_MEM);
    }
#ifdef LCD_DMA
    draw_buffer2 = heap_caps_malloc(draw_buffer_size, heap_caps);
    if(draw_buffer2==NULL) {
        ESP_ERROR_CHECK(ESP_ERR_NO_MEM);
    }
#endif
}

void* lcd_transfer_buffer(void) { return draw_buffer; }
#ifdef LCD_DMA
void* lcd_transfer_buffer2(void) { return draw_buffer2; }
#endif