/**
 * @file point.h
 * @author Radu-D. Chira (github.com/RaduCh04)
 * @brief 
 * @version 0.1
 * @date 2025-05-04
 * 
 */

//TODO: Migrate to C++ for function overloadind?

#include <stdint.h>

/**
 * @brief Draws a single pixel on the display
 *
 * If the coordinates are outside the display boundaries, no action is taken.
 *
 * @param x x-coordinate of the pixel
 * @param y y-coordinate of the pixel
 * @param color 4 byte integer representing the color in RGBA format
 */
void draw_point(int32_t x, int32_t y, uint32_t color);

// TODO: Add description
void draw_point_thick(int32_t x, int32_t y, int32_t thickness, uint32_t color);