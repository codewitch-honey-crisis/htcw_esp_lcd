#ifndef PANELS_H
#define PANELS_H

// BEGIN devices (add more)

#ifdef TTGO_T1
#define LCD_SPI_HOST    SPI3_HOST
#define LCD_PIN_NUM_MOSI 19
#define LCD_PIN_NUM_CLK 18
#define LCD_PIN_NUM_CS 5
#define LCD_PIN_NUM_DC 16
#define LCD_PIN_NUM_RST 23
#define LCD_PIN_NUM_BCKL 4
#define LCD_PANEL esp_lcd_new_panel_st7789
#define LCD_HRES 135
#define LCD_VRES 240
#define LCD_COLOR_SPACE LCD_COLOR_RGB
#define LCD_CLOCK_HZ (40 * 1000 * 1000)
#define LCD_GAP_X 40
#define LCD_GAP_Y 52
#define LCD_MIRROR_X false
#define LCD_MIRROR_Y true
#define LCD_INVERT_COLOR true
#define LCD_SWAP_XY true
#define LCD_DIVISOR 2
#define BUTTON_MASK (BUTTON_PIN(0)|BUTTON_PIN(35))
#define BUTTON_ON_LEVEL 0
#endif // TTGO_T1

#ifdef ESP_WROVER_KIT
#include "esp_lcd_panel_ili9341.h"
#define LCD_BCKL_ON_LEVEL 0
#define LCD_SPI_HOST    SPI3_HOST
#define LCD_PIN_NUM_MISO 25
#define LCD_PIN_NUM_MOSI 23
#define LCD_PIN_NUM_CLK  19
#define LCD_PIN_NUM_CS   22
#define LCD_PIN_NUM_DC   21
#define LCD_PIN_NUM_RST  18
#define LCD_PIN_NUM_BCKL 5
#define LCD_PANEL esp_lcd_new_panel_ili9341
#define LCD_HRES 240
#define LCD_VRES 320
#define LCD_COLOR_SPACE LCD_COLOR_BGR
#define LCD_CLOCK_HZ (40 * 1000 * 1000)
#define LCD_GAP_X 0
#define LCD_GAP_Y 0
#define LCD_MIRROR_X false
#define LCD_MIRROR_Y false
#define LCD_INVERT_COLOR false
#define LCD_SWAP_XY true
#define BUTTON_MASK (BUTTON_PIN(0))
#define BUTTON_ON_LEVEL 0
#endif // ESP_WROVER_KIT

#ifdef M5STACK_CORE2
#include "esp_lcd_panel_ili9342.h"
#define LCD_SPI_HOST    SPI3_HOST
#define LCD_PIN_NUM_MOSI 23
#define LCD_PIN_NUM_CLK 18
#define LCD_PIN_NUM_CS 5
#define LCD_PIN_NUM_DC 15
#define LCD_PANEL esp_lcd_new_panel_ili9342
#define LCD_HRES 320
#define LCD_VRES 240
#define LCD_COLOR_SPACE LCD_COLOR_BGR
#define LCD_CLOCK_HZ (40 * 1000 * 1000)
#define LCD_GAP_X 0
#define LCD_GAP_Y 0
#define LCD_MIRROR_X false
#define LCD_MIRROR_Y false
#define LCD_INVERT_COLOR true
#define LCD_SWAP_XY false
#endif // M5STACK_CORE2

#ifdef M5STACK_FIRE
#include "esp_lcd_panel_ili9342.h"
#define LCD_SPI_HOST    SPI3_HOST
#define LCD_PIN_NUM_MOSI 23
#define LCD_PIN_NUM_CLK 18
#define LCD_PIN_NUM_CS 14
#define LCD_PIN_NUM_DC 27
#define LCD_PIN_NUM_RST 33
#define LCD_PIN_NUM_BCKL 32
#define LCD_PANEL esp_lcd_new_panel_ili9342
#define LCD_HRES 240
#define LCD_VRES 320
#define LCD_COLOR_SPACE LCD_COLOR_BGR
#define LCD_CLOCK_HZ (40 * 1000 * 1000)
#define LCD_GAP_X 0
#define LCD_GAP_Y 0
#define LCD_MIRROR_X false
#define LCD_MIRROR_Y false
#define LCD_INVERT_COLOR true
#define LCD_SWAP_XY true
#endif // M5STACK_FIRE

#ifdef MATOUCH_ESP_DISPLAY_PARALLEL_4
#define LCD_PIN_NUM_CS 1
#define LCD_PIN_NUM_SCK 12
#define LCD_PIN_NUM_SDA 11 
#define LCD_PIN_NUM_DE 45
#define LCD_PIN_NUM_VSYNC 4
#define LCD_PIN_NUM_HSYNC 5
#define LCD_PIN_NUM_CLK 21
#define LCD_PIN_NUM_D00 6
#define LCD_PIN_NUM_D01 7
#define LCD_PIN_NUM_D02 15
#define LCD_PIN_NUM_D03 16
#define LCD_PIN_NUM_D04 8
#define LCD_PIN_NUM_D05 0
#define LCD_PIN_NUM_D06 9
#define LCD_PIN_NUM_D07 14
#define LCD_PIN_NUM_D08 47
#define LCD_PIN_NUM_D09 48
#define LCD_PIN_NUM_D10 3
#define LCD_PIN_NUM_D11 39
#define LCD_PIN_NUM_D12 40
#define LCD_PIN_NUM_D13 41
#define LCD_PIN_NUM_D14 42
#define LCD_PIN_NUM_D15 2
#define LCD_PIN_NUM_BCKL -1
#define LCD_HSYNC_POLARITY 1
#define LCD_HSYNC_FRONT_PORCH 10
#define LCD_HSYNC_PULSE_WIDTH 8
#define LCD_HSYNC_BACK_PORCH 50
#define LCD_VSYNC_POLARITY 1
#define LCD_VSYNC_FRONT_PORCH 10
#define LCD_VSYNC_PULSE_WIDTH 8
#define LCD_VSYNC_BACK_PORCH 10
#define LCD_CLK_IDLE_HIGH 0
#define LCD_DE_IDLE_HIGH 1
#define LCD_BIT_DEPTH 16
#define LCD_PANEL esp_lcd_new_panel_st7701
#define LCD_HRES 480
#define LCD_VRES 480
#define LCD_COLOR_SPACE LCD_COLOR_BGR
#define LCD_SWAP_COLOR_BYTES true
#ifdef CONFIG_SPIRAM_MODE_QUAD
    #define LCD_CLOCK_HZ (6 * 1000 * 1000)
#else
    #define LCD_CLOCK_HZ (10 * 1000 * 1000)
#endif
#endif // MATOUCH_ESP_DISPLAY_PARALLEL_4

#ifdef MATOUCH_ESP_DISPLAY_PARALLEL_43
#include "esp_lcd_touch_gt911.h"
#define LCD_PIN_NUM_DE 40
#define LCD_PIN_NUM_VSYNC 41
#define LCD_PIN_NUM_HSYNC 39
#define LCD_PIN_NUM_CLK 42
#define LCD_PIN_NUM_D00 8
#define LCD_PIN_NUM_D01 2
#define LCD_PIN_NUM_D02 46
#define LCD_PIN_NUM_D03 9
#define LCD_PIN_NUM_D04 1
#define LCD_PIN_NUM_D05 5
#define LCD_PIN_NUM_D06 6
#define LCD_PIN_NUM_D07 7
#define LCD_PIN_NUM_D08 15
#define LCD_PIN_NUM_D09 16
#define LCD_PIN_NUM_D10 4
#define LCD_PIN_NUM_D11 45
#define LCD_PIN_NUM_D12 48
#define LCD_PIN_NUM_D13 47
#define LCD_PIN_NUM_D14 21
#define LCD_PIN_NUM_D15 14
#define LCD_PIN_NUM_BCKL -1
#define LCD_HSYNC_POLARITY 0
#define LCD_HSYNC_FRONT_PORCH 8
#define LCD_HSYNC_PULSE_WIDTH 4
#define LCD_HSYNC_BACK_PORCH 8
#define LCD_VSYNC_POLARITY 0
#define LCD_VSYNC_FRONT_PORCH 8
#define LCD_VSYNC_PULSE_WIDTH 4
#define LCD_VSYNC_BACK_PORCH 8
#define LCD_CLK_IDLE_HIGH 0
#define LCD_DE_IDLE_HIGH 0
#define LCD_BIT_DEPTH 16
#define LCD_HRES 800
#define LCD_VRES 480
#define LCD_COLOR_SPACE LCD_COLOR_BGR
#define LCD_SWAP_COLOR_BYTES false
#define LCD_TRANSFER_IN_SPIRAM
#ifdef CONFIG_SPIRAM_MODE_QUAD
    #define LCD_CLOCK_HZ (6 * 1000 * 1000)
#else
    #define LCD_CLOCK_HZ (16 * 1000 * 1000)
#endif
#define TOUCH_I2C_HOST I2C_NUM_0
#define TOUCH_PIN_NUM_SCL 18
#define TOUCH_PIN_NUM_SDA 17

#define TOUCH_PANEL esp_lcd_touch_new_i2c_gt911
#define TOUCH_ADDRESS ESP_LCD_TOUCH_IO_I2C_GT911_ADDRESS
#define TOUCH_CMD_BITS 16
#define TOUCH_PARAM_BITS 0
#define TOUCH_DISABLE_CONTROL_PHASE
#define TOUCH_CLOCK_HZ (400*1000)
#define TOUCH_PIN_NUM_RST 38
#define TOUCH_HRES 480
#define TOUCH_VRES 272
#endif // MATOUCH_ESP_DISPLAY_PARALLEL_43

#ifdef MATOUCH_ESP_DISPLAY_PARALLEL_7
#define LCD_BCKL_ON_LEVEL 0
#define LCD_PIN_NUM_DE 40
#define LCD_PIN_NUM_VSYNC 41
#define LCD_PIN_NUM_HSYNC 39
#define LCD_PIN_NUM_CLK 42
#define LCD_PIN_NUM_D00 8
#define LCD_PIN_NUM_D01 3
#define LCD_PIN_NUM_D02 46
#define LCD_PIN_NUM_D03 9
#define LCD_PIN_NUM_D04 1
#define LCD_PIN_NUM_D05 5
#define LCD_PIN_NUM_D06 6
#define LCD_PIN_NUM_D07 7
#define LCD_PIN_NUM_D08 15
#define LCD_PIN_NUM_D09 16
#define LCD_PIN_NUM_D10 4
#define LCD_PIN_NUM_D11 45
#define LCD_PIN_NUM_D12 48
#define LCD_PIN_NUM_D13 47
#define LCD_PIN_NUM_D14 21
#define LCD_PIN_NUM_D15 14
#define LCD_PIN_NUM_BCKL 10
#define LCD_HSYNC_POLARITY 1
//#define LCD_HSYNC_FRONT_PORCH 40
#define LCD_HSYNC_FRONT_PORCH 210
//#define LCD_HSYNC_PULSE_WIDTH 48
#define LCD_HSYNC_PULSE_WIDTH 30
//#define LCD_HSYNC_BACK_PORCH 128
#define LCD_HSYNC_BACK_PORCH 16
//#define LCD_VSYNC_POLARITY 1
#define LCD_VSYNC_POLARITY 0
//#define LCD_VSYNC_FRONT_PORCH 13
#define LCD_VSYNC_FRONT_PORCH 22
//#define LCD_VSYNC_PULSE_WIDTH 3
#define LCD_VSYNC_PULSE_WIDTH 13
//#define LCD_VSYNC_BACK_PORCH 45
#define LCD_VSYNC_BACK_PORCH 10
#define LCD_CLK_IDLE_HIGH 1 
#define LCD_DE_IDLE_HIGH 0
#define LCD_BIT_DEPTH 16

//#define LCD_PANEL esp_lcd_new_panel_st7701
#define LCD_HRES 1024
#define LCD_VRES 600
//#define LCD_SWAP_HRES_VRES_TIMING
#define LCD_COLOR_SPACE LCD_COLOR_BGR
#define LCD_SWAP_COLOR_BYTES false
#ifdef CONFIG_SPIRAM_MODE_QUAD
    #define LCD_CLOCK_HZ (6 * 1000 * 1000)
#else
    #define LCD_CLOCK_HZ (10 * 1000 * 1000)
#endif
#define LCD_PSRAM_BUFFER (1024*100*2)
#endif // MATOUCH_ESP_DISPLAY_PARALLEL_7
#ifdef WAVESHARE_S3_43_DEVKIT
#include "esp_lcd_touch_gt911.h"
#define LCD_PIN_NUM_DE 5
#define LCD_PIN_NUM_VSYNC 3
#define LCD_PIN_NUM_HSYNC 46
#define LCD_PIN_NUM_CLK 7
#define LCD_PIN_NUM_D00 14
#define LCD_PIN_NUM_D01 38
#define LCD_PIN_NUM_D02 18
#define LCD_PIN_NUM_D03 17
#define LCD_PIN_NUM_D04 10
#define LCD_PIN_NUM_D05 39
#define LCD_PIN_NUM_D06 0
#define LCD_PIN_NUM_D07 45
#define LCD_PIN_NUM_D08 48
#define LCD_PIN_NUM_D09 47
#define LCD_PIN_NUM_D10 21
#define LCD_PIN_NUM_D11 1
#define LCD_PIN_NUM_D12 2
#define LCD_PIN_NUM_D13 42
#define LCD_PIN_NUM_D14 41
#define LCD_PIN_NUM_D15 40
#define LCD_PIN_NUM_BCKL -1
#define LCD_HSYNC_POLARITY 0
#define LCD_HSYNC_FRONT_PORCH 20
#define LCD_HSYNC_PULSE_WIDTH 10
#define LCD_HSYNC_BACK_PORCH 10
#define LCD_VSYNC_POLARITY 0
#define LCD_VSYNC_FRONT_PORCH 10
#define LCD_VSYNC_PULSE_WIDTH 10
#define LCD_VSYNC_BACK_PORCH 10
#define LCD_CLK_IDLE_HIGH 0
#define LCD_DE_IDLE_HIGH 0
#define LCD_BIT_DEPTH 16

//#define LCD_PANEL esp_lcd_new_panel_st7701
#define LCD_HRES 800
#define LCD_VRES 480
#define LCD_SWAP_HRES_VRES_TIMING
#define LCD_COLOR_SPACE LCD_COLOR_BGR
#define LCD_SWAP_COLOR_BYTES false
#ifdef CONFIG_SPIRAM_MODE_QUAD
    #define LCD_CLOCK_HZ (6 * 1000 * 1000)
#else
    #define LCD_CLOCK_HZ (14 * 1000 * 1000)
#endif
#define TOUCH_I2C_HOST I2C_NUM_0
#define TOUCH_PIN_NUM_SCL           9
#define TOUCH_PIN_NUM_SDA           8

#define TOUCH_PANEL esp_lcd_touch_new_i2c_gt911
#define TOUCH_ADDRESS ESP_LCD_TOUCH_IO_I2C_GT911_ADDRESS
#define TOUCH_CMD_BITS 16
#define TOUCH_PARAM_BITS 0
#define TOUCH_DISABLE_CONTROL_PHASE
#define TOUCH_CLOCK_HZ (400*1000)
#define TOUCH_HRES LCD_HRES
#define TOUCH_VRES LCD_VRES

#ifndef LEGACY_I2C
#define TOUCH_RESET \
    i2c_master_bus_handle_t bus; \
    ESP_ERROR_CHECK(i2c_master_get_bus_handle((i2c_port_num_t)0,&bus)); \
    i2c_master_dev_handle_t i2c=NULL; \
    i2c_device_config_t dev_cfg; \
    memset(&dev_cfg,0,sizeof(dev_cfg)); \
    dev_cfg.scl_speed_hz = 200*1000; \
    dev_cfg.device_address = 0x24; \
    dev_cfg.dev_addr_length = I2C_ADDR_BIT_LEN_7; \
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus, &dev_cfg,&i2c)); \
    uint8_t write_buf = 0x01; \
    ESP_ERROR_CHECK(i2c_master_transmit(i2c,&write_buf,1,1000 )); \
    ESP_ERROR_CHECK(i2c_master_bus_rm_device(i2c)); \
    dev_cfg.device_address = 0x38; \
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus, &dev_cfg,&i2c)); \
    write_buf = 0x2C; \
    ESP_ERROR_CHECK(i2c_master_transmit(i2c,&write_buf,1,1000 )); \
    esp_rom_delay_us(100 * 1000); \
    gpio_set_level((gpio_num_t)4, 0); \
    esp_rom_delay_us(100 * 1000); \
    write_buf = 0x2E; \
    ESP_ERROR_CHECK(i2c_master_transmit(i2c,&write_buf,1,1000 )); \
    esp_rom_delay_us(200 * 1000); \
    ESP_ERROR_CHECK(i2c_master_bus_rm_device(i2c))
#else
#define TOUCH_RESET \
    uint8_t write_buf = 0x01;\
    ESP_ERROR_CHECK(i2c_master_write_to_device((i2c_port_t)0,0x24,&write_buf,1,portMAX_DELAY));\
    write_buf = 0x2c;\
    ESP_ERROR_CHECK(i2c_master_write_to_device((i2c_port_t)0,0x38,&write_buf,1,portMAX_DELAY));\
    esp_rom_delay_us(100 * 1000);\
    gpio_set_level((gpio_num_t)4, 0);\
    write_buf = 0x2E;\
    ESP_ERROR_CHECK(i2c_master_write_to_device((i2c_port_t)0,0x38,&write_buf,1,portMAX_DELAY));\
    esp_rom_delay_us(200 * 1000)
#endif
#endif // WAVESHARE_S3_43_DEVKIT

#ifdef T_DISPLAY_S3
#define LCD_PIN_NUM_CS 6
#define LCD_PIN_NUM_RST 5
#define LCD_PIN_NUM_WR 8
#define LCD_PIN_NUM_RD 9
#define LCD_PIN_NUM_RS 7
#define LCD_PIN_NUM_D00 39
#define LCD_PIN_NUM_D01 40
#define LCD_PIN_NUM_D02 41
#define LCD_PIN_NUM_D03 42
#define LCD_PIN_NUM_D04 45
#define LCD_PIN_NUM_D05 46
#define LCD_PIN_NUM_D06 47
#define LCD_PIN_NUM_D07 48
#define LCD_PIN_NUM_BCKL 38
#define LCD_PANEL esp_lcd_new_panel_st7789
#define LCD_HRES 170
#define LCD_VRES 320
#define LCD_COLOR_SPACE LCD_COLOR_RGB
#define LCD_CLOCK_HZ (6528 * 1000)
#define LCD_GAP_X 0
#define LCD_GAP_Y 35
#define LCD_MIRROR_X false
#define LCD_MIRROR_Y true
#define LCD_INVERT_COLOR true
#define LCD_SWAP_XY true
#endif // T_DISPLAY_S3

#ifdef S3_T_QT
#define LCD_SPI_HOST    SPI3_HOST
#define LCD_BCKL_ON_LEVEL 0
#define LCD_PIN_NUM_MOSI 2
#define LCD_PIN_NUM_CLK 3
#define LCD_PIN_NUM_CS 5
#define LCD_PIN_NUM_DC 6
#define LCD_PIN_NUM_RST 1
#define LCD_PIN_NUM_BCKL 10
#define LCD_PANEL esp_lcd_new_panel_st7789
#define LCD_HRES 128
#define LCD_VRES 128
#define LCD_COLOR_SPACE LCD_COLOR_BGR
#define LCD_CLOCK_HZ (40 * 1000 * 1000)
#define LCD_GAP_X 2
#define LCD_GAP_Y 1
#define LCD_MIRROR_X true
#define LCD_MIRROR_Y true
#define LCD_INVERT_COLOR true
#define LCD_SWAP_XY false
#endif // S3_T_QT

#ifdef M5STACK_S3_ATOM
#define LCD_SPI_HOST    SPI3_HOST
#define LCD_PIN_NUM_MOSI 21
#define LCD_PIN_NUM_CLK 17
#define LCD_PIN_NUM_CS 15
#define LCD_PIN_NUM_DC 33
#define LCD_PIN_NUM_RST 34
#define LCD_PIN_NUM_BCKL 16
#define LCD_PANEL esp_lcd_new_panel_st7789
#define LCD_HRES 128
#define LCD_VRES 128
#define LCD_COLOR_SPACE LCD_COLOR_BGR
#define LCD_CLOCK_HZ (40 * 1000 * 1000)
#define LCD_GAP_X 2
#define LCD_GAP_Y 1
#define LCD_MIRROR_X true
#define LCD_MIRROR_Y true
#define LCD_INVERT_COLOR true
#define LCD_SWAP_XY false
#endif // M5STACK_S3_ATOM

#ifdef T_RGB
#define LCD_PIN_NUM_DE 45
#define LCD_PIN_NUM_VSYNC 41
#define LCD_PIN_NUM_HSYNC 47
#define LCD_PIN_NUM_CLK 42
#define LCD_PIN_NUM_D00 21
#define LCD_PIN_NUM_D01 18
#define LCD_PIN_NUM_D02 17
#define LCD_PIN_NUM_D03 16
#define LCD_PIN_NUM_D04 15
#define LCD_PIN_NUM_D05 14
#define LCD_PIN_NUM_D06 13
#define LCD_PIN_NUM_D07 12
#define LCD_PIN_NUM_D08 11
#define LCD_PIN_NUM_D09 10
#define LCD_PIN_NUM_D10 9
#define LCD_PIN_NUM_D11 7
#define LCD_PIN_NUM_D12 6
#define LCD_PIN_NUM_D13 5
#define LCD_PIN_NUM_D14 3
#define LCD_PIN_NUM_D15 2
#define LCD_PIN_NUM_BCKL 46
#define LCD_HSYNC_POLARITY 0
#define LCD_HSYNC_FRONT_PORCH 50
#define LCD_HSYNC_PULSE_WIDTH 1
#define LCD_HSYNC_BACK_PORCH 30
#define LCD_VSYNC_POLARITY 0
#define LCD_VSYNC_FRONT_PORCH 20
#define LCD_VSYNC_PULSE_WIDTH 1
#define LCD_VSYNC_BACK_PORCH 30
#define LCD_CLK_IDLE_HIGH 0
#define LCD_DE_IDLE_HIGH 0
#define LCD_BIT_DEPTH 16
#define LCD_PANEL esp_lcd_new_panel_st7701_t_rgb
#define LCD_HRES 480
#define LCD_VRES 480
#define LCD_COLOR_SPACE LCD_COLOR_BGR
#define LCD_SWAP_COLOR_BYTES false
#ifdef CONFIG_SPIRAM_MODE_QUAD
    #define LCD_CLOCK_HZ (6 * 1000 * 1000)
#else
    #define LCD_CLOCK_HZ (8 * 1000 * 1000)
#endif
#endif // T_RGB

#ifdef SUNTON_7INCH
#define LCD_PIN_NUM_DE 41
#define LCD_PIN_NUM_VSYNC 40
#define LCD_PIN_NUM_HSYNC 39
#define LCD_PIN_NUM_CLK 42
#define LCD_PIN_NUM_D00 14
#define LCD_PIN_NUM_D01 21
#define LCD_PIN_NUM_D02 47
#define LCD_PIN_NUM_D03 48
#define LCD_PIN_NUM_D04 45
#define LCD_PIN_NUM_D05 9
#define LCD_PIN_NUM_D06 46
#define LCD_PIN_NUM_D07 3
#define LCD_PIN_NUM_D08 8
#define LCD_PIN_NUM_D09 16
#define LCD_PIN_NUM_D10 1
#define LCD_PIN_NUM_D11 15
#define LCD_PIN_NUM_D12 7
#define LCD_PIN_NUM_D13 6
#define LCD_PIN_NUM_D14 5
#define LCD_PIN_NUM_D15 4
#define LCD_PIN_NUM_BCKL 2
#define LCD_HSYNC_POLARITY 0
#define LCD_HSYNC_FRONT_PORCH 210
#define LCD_HSYNC_PULSE_WIDTH 30
#define LCD_HSYNC_BACK_PORCH 16
#define LCD_VSYNC_POLARITY 0
#define LCD_VSYNC_FRONT_PORCH 22
#define LCD_VSYNC_PULSE_WIDTH 13
#define LCD_VSYNC_BACK_PORCH 10
#define LCD_CLK_ACTIVE_NEG 1
#define LCD_CLK_IDLE_HIGH 0
#define LCD_DE_IDLE_HIGH 1
#define LCD_BIT_DEPTH 16
//#define LCD_PANEL esp_lcd_new_panel_st7701
#define LCD_HRES 800
#define LCD_VRES 480
#define LCD_COLOR_SPACE LCD_COLOR_BGR
#define LCD_SWAP_COLOR_BYTES false
#ifdef CONFIG_SPIRAM_MODE_QUAD
    #define LCD_CLOCK_HZ (6 * 1000 * 1000)
#else
    #define LCD_CLOCK_HZ (16 * 1000 * 1000)
#endif
#endif // SUNTON_7INCH

#ifdef HELTEC_WIFI_LORA_KIT_V2
#if __has_include(<ssd1306_surface_adapter.hpp>)
#include <ssd1306_surface_adapter.hpp>
#endif
#define LCD_I2C_HOST    0
#define LCD_I2C_ADDR 0x3C
#define LCD_CONTROL_PHASE_BYTES 1
#define LCD_DC_BIT_OFFSET 6
#define LCD_BIT_DEPTH 1
#define LCD_PIN_NUM_SCL 15
#define LCD_PIN_NUM_SDA 4
#define LCD_PIN_NUM_RST 16
#define LCD_PANEL esp_lcd_new_panel_ssd1306
#define LCD_HRES 128
#define LCD_VRES 64
#define LCD_COLOR_SPACE LCD_COLOR_GSC
#define LCD_CLOCK_HZ (400 * 1000)
#define LCD_GAP_X 0
#define LCD_GAP_Y 0
#define LCD_MIRROR_X true
#define LCD_MIRROR_Y true
#define LCD_INVERT_COLOR false
#define LCD_SWAP_XY false
#define LCD_FRAME_ADAPTER ssd1306_surface_adapter
#define LCD_Y_ALIGN 8
#define LCD_VENDOR_CONFIG esp_lcd_panel_ssd1306_config_t vendor_config = {\
    .height = LCD_VRES,\
};
#endif // HELTEC_WIFI_LORA_KIT_V2

#ifdef ESP_USB_OTG
#define LCD_SPI_HOST    SPI2_HOST
#define LCD_PIN_NUM_MOSI 7
#define LCD_PIN_NUM_CLK 6
#define LCD_PIN_NUM_CS 5
#define LCD_PIN_NUM_DC 4
#define LCD_PIN_NUM_RST 8
#define LCD_PIN_NUM_BCKL 9
#define LCD_PANEL esp_lcd_new_panel_st7789
#define LCD_HRES 240
#define LCD_VRES 240
#define LCD_COLOR_SPACE LCD_COLOR_RGB
#define LCD_CLOCK_HZ (40 * 1000 * 1000)
#define LCD_GAP_X 0
#define LCD_GAP_Y 0
#define LCD_MIRROR_X false
#define LCD_MIRROR_Y false
#define LCD_INVERT_COLOR true
#define LCD_SWAP_XY false
#endif // ESP_USB_OTG

#ifdef WAVESHARE_P4_SMART86BOX
#include "esp_lcd_st7703.h"
#define LCD_TRANSFER_IN_SPIRAM
#define LCD_BCKL_ON_LEVEL 0
#define LCD_HRES 720
#define LCD_VRES 720
#define LCD_HSYNC_FRONT_PORCH 80
#define LCD_HSYNC_PULSE_WIDTH 20
#define LCD_HSYNC_BACK_PORCH 80
#define LCD_VSYNC_FRONT_PORCH 30
#define LCD_VSYNC_PULSE_WIDTH 4
#define LCD_VSYNC_BACK_PORCH 12
#define LCD_BIT_DEPTH 16
#define LCD_MIPI_DMA2D
#define LCD_PANEL esp_lcd_new_panel_st7703
#define LCD_DATA_ENDIAN_LITTLE
#define LCD_MIPI_DSI_PHY_PWR_LDO_CHAN (3)
#define LCD_MIPI_DSI_PHY_PWR_LDO_VOLTAGE_MV (2500)
#define LCD_VENDOR_CONFIG \
st7703_vendor_config_t vendor_config = { \
    .mipi_config = { \
        .dsi_bus = mipi_dsi_bus, \
        .dpi_config = &dpi_config, \
    }, \
    .flags = { \
        .use_mipi_interface = 1, \
    }, \
}
#define LCD_PIN_NUM_RST 27
#define LCD_PIN_NUM_BCKL 26
#define LCD_PHY_PWR_LDO_CHAN
#define LCD_CLOCK_HZ (46 * 1000 * 1000)
#endif // WAVESHARE_P4_SMART86BOX

#ifdef MATOUCH_ESP_DISPLAY_PARALLEL_35
#include "esp_lcd_panel_ili9488.h"
#define LCD_PIN_NUM_CS 37
#define LCD_PIN_NUM_WR 35
#define LCD_PIN_NUM_RD 48
#define LCD_PIN_NUM_RS 36
#define LCD_PIN_NUM_D00 47
#define LCD_PIN_NUM_D01 21
#define LCD_PIN_NUM_D02 14
#define LCD_PIN_NUM_D03 13
#define LCD_PIN_NUM_D04 12
#define LCD_PIN_NUM_D05 11
#define LCD_PIN_NUM_D06 10
#define LCD_PIN_NUM_D07 9
#define LCD_PIN_NUM_D08 3
#define LCD_PIN_NUM_D09 8
#define LCD_PIN_NUM_D10 16
#define LCD_PIN_NUM_D11 15
#define LCD_PIN_NUM_D12 7
#define LCD_PIN_NUM_D13 6
#define LCD_PIN_NUM_D14 5
#define LCD_PIN_NUM_D15 4
#define LCD_PIN_NUM_BCKL 45
#define LCD_PANEL esp_lcd_new_panel_ili9488
#define LCD_HRES 320
#define LCD_VRES 480
#define LCD_COLOR_SPACE LCD_COLOR_BGR
#define LCD_CLOCK_HZ (20 * 1000 * 1000)
#define LCD_GAP_X 0
#define LCD_GAP_Y 0
#define LCD_MIRROR_X true
#define LCD_MIRROR_Y true
#define LCD_INVERT_COLOR false
#define LCD_SWAP_XY true
#define LCD_SWAP_COLOR_BYTES true
#endif // MATOUCH_ESP_DISPLAY_PARALLEL_35

#ifdef FREENOVE_S3_DEVKIT
#include "esp_lcd_touch_ft6x36.h"
#define LCD_SPI_HOST SPI3_HOST
#define LCD_PIN_NUM_DC 0
#define LCD_PIN_NUM_CS 47
#define LCD_PIN_NUM_MOSI 20
#define LCD_PIN_NUM_CLK 21
#define LCD_HRES 240
#define LCD_VRES 320
#define LCD_COLOR_SPACE LCD_COLOR_BGR
#define LCD_CLOCK_HZ (80 * 1000 * 1000)
#define LCD_MIRROR_X true
#define LCD_MIRROR_Y false
#define LCD_PANEL esp_lcd_new_panel_st7789
#define LCD_INVERT_COLOR false
#define LCD_SWAP_XY true

#define TOUCH_I2C_HOST I2C_NUM_0
#define TOUCH_PIN_NUM_SCL 1
#define TOUCH_PIN_NUM_SDA 2

#define TOUCH_PANEL esp_lcd_touch_new_i2c_ft6x36
#define TOUCH_ADDRESS ESP_LCD_TOUCH_IO_I2C_FT6x36_ADDRESS
#define TOUCH_CMD_BITS 8
#define TOUCH_PARAM_BITS 0
#define TOUCH_DISABLE_CONTROL_PHASE
#define TOUCH_CLOCK_HZ (200*1000)
#define TOUCH_PIN_NUM_RST -1

#endif // FREENOVE_S3_DEVKIT

// For testing. No actual integrated display
#ifdef C6DEVKITC1
#if __has_include("ssd1306_surface_adapter.hpp")
#include "ssd1306_surface_adapter.hpp"
#endif
#define LCD_I2C_HOST    0
#define LCD_DMA
#define LCD_I2C_ADDR 0x3C
#define LCD_CONTROL_PHASE_BYTES 1
#define LCD_DC_BIT_OFFSET 6
#define LCD_BIT_DEPTH 1
#define LCD_PIN_NUM_SCL 11
#define LCD_PIN_NUM_SDA 10
#define LCD_PIN_NUM_RST -1
#define LCD_PANEL esp_lcd_new_panel_ssd1306
#define LCD_HRES 128
#define LCD_VRES 32
#define LCD_COLOR_SPACE LCD_COLOR_GSC
#define LCD_CLOCK_HZ (400 * 1000)
#define LCD_GAP_X 0
#define LCD_GAP_Y 0
#define LCD_MIRROR_X true
#define LCD_MIRROR_Y true
#define LCD_INVERT_COLOR false
#define LCD_SWAP_XY false
#define LCD_FRAME_ADAPTER ssd1306_surface_adapter
#define LCD_Y_ALIGN 8
#define LCD_VENDOR_CONFIG esp_lcd_panel_ssd1306_config_t vendor_config = {\
    .height = LCD_VRES,\
};
#endif // C6DEVKITC1

// END devices

#endif // PANELS_H