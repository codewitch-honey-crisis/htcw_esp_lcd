#ifndef PANEL_H
#define PANEL_H
#include "panel_config.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#ifdef LCD_BUS
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
#if LCD_TRANSFER_SIZE > 0
/// @brief Returns the transfer buffer 
/// @return A pointer to the transfer buffer, of size LCD_TRANSFER_SIZE
void* lcd_transfer_buffer(void);
#ifdef LCD_DMA
/// @brief Returns the secondary transfer buffer 
/// @return A pointer to the secondary transfer buffer, of size LCD_TRANSFER_SIZE
void* lcd_transfer_buffer2(void);
#endif
#endif
/// @brief Indicates how many draws have occurred since the vblanking period was active
/// @return The number of draws that have occurred, or 0 if not supported
size_t lcd_vsync_draw_count(void);
#endif
#ifdef TOUCH_BUS
/// @brief Initializes the touch panel
void touch_init(void);
/// @brief Updated the touch panel date
void touch_update(void);
/// @brief Reads the touch scaled to the LCD (if present, otherwise, same as touch_read_raw)
/// @param in_out_count The touch count
/// @param out_x The x array
/// @param out_y The y array
/// @param out_strength The strength array
void touch_read(size_t* in_out_count,uint16_t* out_x,uint16_t* out_y, uint16_t* out_strength);
/// @brief Reads the touch unscaled
/// @param in_out_count The touch count
/// @param out_x The x array
/// @param out_y The y array
/// @param out_strength The strength array
void touch_read_raw(size_t* in_out_count,uint16_t* out_x,uint16_t* out_y, uint16_t* out_strength);
#endif
#ifdef __cplusplus
}
#endif
#endif // LCD_H