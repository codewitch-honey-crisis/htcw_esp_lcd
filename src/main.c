/*
 * SPDX-FileCopyrightText: 2021-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <memory.h>
#include "lcd.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define I2C_BUS_PORT  0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// Please update the following configuration according to your LCD spec //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define EXAMPLE_LCD_PIXEL_CLOCK_HZ    (200 * 1000)
#define EXAMPLE_PIN_NUM_SDA           10
#define EXAMPLE_PIN_NUM_SCL           11
#define EXAMPLE_PIN_NUM_RST           -1
#define EXAMPLE_I2C_HW_ADDR           0x3C

// The pixel number in horizontal and vertical
#define EXAMPLE_LCD_H_RES              128
#define EXAMPLE_LCD_V_RES              32
// Bit number used to represent command and parameter
#define EXAMPLE_LCD_CMD_BITS           8
#define EXAMPLE_LCD_PARAM_BITS         8
volatile int flushing = 0;
void lcd_flush_complete(void) {
    flushing = 0;
}
void app_main(void)
{
    vTaskDelay(pdMS_TO_TICKS(1000));
    lcd_init();

    uint8_t buf[(EXAMPLE_LCD_H_RES*EXAMPLE_LCD_V_RES+7)/8];
    while(1) {
        vTaskDelay(5);
        while(flushing) portYIELD(); 
        flushing = 1;
        memset(buf,0xFF,sizeof(buf));
        lcd_flush(0,0,LCD_WIDTH-1,LCD_HEIGHT-1,buf);
        while(flushing) portYIELD(); 
        flushing = 1;
        memset(buf,0x0,sizeof(buf));
        lcd_flush(0,0,LCD_WIDTH-1,LCD_HEIGHT-1,buf);
    }

}