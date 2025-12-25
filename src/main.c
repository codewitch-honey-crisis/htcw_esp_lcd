#include <stdio.h>
#include <memory.h>
#include "panel.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#if defined(LCD_BUS) && LCD_BIT_DEPTH == 16 && LCD_COLOR_SPACE != LCD_COLOR_GSC
#define COLOR_BLACK (0)
#define COLOR_WHITE (0xFFFF)
#define COLOR_RED (31<<11)
#define COLOR_GREEN (63<<5)
#define COLOR_BLUE (31)
#endif

#ifdef LCD_BUS
#ifndef LCD_NO_DMA
volatile int flushing = 0;
void lcd_flush_complete(void) {
    flushing = 0;
}
#endif
#endif
#ifdef COLOR_BLACK
#define CLEAR_DELAY 125
void clear_screen(uint16_t color) {
    uint16_t* buf = (uint16_t*)lcd_transfer_buffer();
    for(int i = 0;i<LCD_TRANSFER_SIZE/2;++i) {
        *buf++=color;
    }
    int y = 0;
    while(y<LCD_HEIGHT) {
        int yend = y+(LCD_HEIGHT/LCD_DIVISOR)-1;
        if(yend>=LCD_HEIGHT) {
            yend = LCD_HEIGHT-1;
        }
#ifndef LCD_NO_DMA
        while(flushing) portYIELD(); 
        flushing = 1;
#endif
        lcd_flush(0,y,LCD_WIDTH-1,yend,lcd_transfer_buffer());
        y= yend+1;
        while(lcd_vsync_flush_count()) portYIELD();
    }
}
#endif
void app_main(void)
{
    vTaskDelay(pdMS_TO_TICKS(1000));
#ifdef LCD_BUS
    lcd_init();
#endif
#ifdef TOUCH_BUS
    touch_init();
#endif
#ifdef BUTTON
    button_init();
#endif
    while(1) {
        vTaskDelay(5);
#ifdef COLOR_BLACK
        clear_screen(COLOR_BLACK);
        vTaskDelay(pdMS_TO_TICKS(CLEAR_DELAY));
        clear_screen(COLOR_RED);
        vTaskDelay(pdMS_TO_TICKS(CLEAR_DELAY));
        clear_screen(COLOR_GREEN);
        vTaskDelay(pdMS_TO_TICKS(CLEAR_DELAY));
        clear_screen(COLOR_BLUE);
        vTaskDelay(pdMS_TO_TICKS(CLEAR_DELAY));
        clear_screen(COLOR_WHITE);
        vTaskDelay(pdMS_TO_TICKS(CLEAR_DELAY));
#endif
#ifdef TOUCH_BUS
        touch_update();
        size_t count = 5;
        uint16_t x[5],y[5],s[5];
        touch_read(&count,x,y,s);
        if(count) {
            printf("touch: (%d, %d)\n",x[0],y[0]);
        }
#endif
#ifdef BUTTON
        uint64_t button_mask = button_read_all();
        if(button_mask>0) {
            printf("Pressed mask: 0x%llx (%lld)\n",button_mask,button_mask);
        }
#endif
    }
}