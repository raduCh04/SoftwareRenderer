/**
 * @file renderer.h
 * @author Radu Chira (github.com/raduCh04)
 * @version 0.1
 * @date 2025-04-12
 *
 * @brief Core 2D rendering routines including line, circle, and polygon drawing.
 *
 * @note Colors are stored in RGBA format (Alpha, Red, Green, Blue), rather than RGBA.
 *
 * Each pixel in the `pixmap` is a 32-bit signed integer, where:
 *   - Bits 24–31: Red
 *   - Bits 16–23: Green
 *   - Bits 8–15 : Blue
 *   - Bits 0–7  : Alpha
 */

#include <stdint.h>

#include "defs.h"
#include "point.h"
#include "line.h"
#include "circle.h"

/**
 * @brief Clears the entire display to a specified color
 *
 * Fills the entire pixmap with the given color value.
 *
 * @param color 4 byte integer representing the color in RGBA format
 */
void pixmap_clear(uint32_t color);

/**
 * @brief Exports the current state of the pixmap to a file
 *
 * Saves the `pixmap` array to a file named "pixmap.data" in binary format.
 * This can be used to visualize the frame buffer or debug the rendering output.
 */
void pixmap_export(void);

