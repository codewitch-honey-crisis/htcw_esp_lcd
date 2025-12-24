#ifndef LCD_H
#define LCD_H
#include "lcd_config.h"
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
/// @brief Initializes the display
void lcd_init(void);
/// @brief Sends a bitmap to the display
/// @param x1 The x1 coord
/// @param y1 The y1 coord
/// @param x2 The x2 coord
/// @param y2 The y2 coord
/// @param bitmap The bitmap data
void lcd_flush(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, void* bitmap);
/// @brief Called when a transfer is complete. To be implemented by the lcd_init() caller
void lcd_flush_complete(void);
#ifdef __cplusplus
}
#endif
#endif // LCD_H