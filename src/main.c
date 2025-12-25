#include <stdio.h>
#include <memory.h>
#include "panel.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#ifdef LCD_BUS
volatile int flushing = 0;
void lcd_flush_complete(void) {
    flushing = 0;
}
void clear_screen(uint16_t color) {
    vTaskDelay(5);
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
        while(flushing) portYIELD(); 
        flushing = 1;
        lcd_flush(0,y,LCD_WIDTH-1,yend,lcd_transfer_buffer());
        y= yend+1;
        while(lcd_vsync_draw_count()) portYIELD();
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
    while(1) {
#ifdef LCD_BUS
        clear_screen(0xFFFF);
        clear_screen(0x0000);
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
    }
}