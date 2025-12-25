#include <stdio.h>
#include <memory.h>
#include "lcd.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

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
        printf("flushing %d - %d\n",y,yend);
        lcd_flush(0,y,LCD_WIDTH-1,yend,lcd_transfer_buffer());
        y= yend+1;
    }
}
void app_main(void)
{
    vTaskDelay(pdMS_TO_TICKS(1000));
    lcd_init();
    while(1) {
        clear_screen(0xFFFF);
        clear_screen(0x0000);
    }
}