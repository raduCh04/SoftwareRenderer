/**
 * @file line.h
 * @author Radu-D. Chira (github.com/RaduCh04)
 * @brief 
 * @version 0.1
 * @date 2025-05-04
 * 
 */

#include <stdint.h>

/**
 * @brief Draws a straight line using the slope-intercept method (y = mx + b)
 *
 * Handles special cases like horizontal and vertical lines. For other slopes,
 * it calculates the y-value using floating-point math and draws a point at each x.
 *
 * @note This is a basic implementation and not optimal for performance or steep lines.
 *
 * @param x0 Starting x-coordinate
 * @param y0 Starting y-coordinate
 * @param x1 Ending x-coordinate
 * @param y1 Ending y-coordinate
 * @param color 4 byte integer representing the color in RGBA format
 */
void draw_line_equation(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);

/**
 * @brief Draws a straight line using the incremental (floating-point) method.
 *
 * Uses the slope `m` to incrementally compute y from x in floating point.
 * Suitable for all slopes but slower than integer-based methods.
 *
 * @param x0 Starting x-coordinate.
 * @param y0 Starting y-coordinate.
 * @param x1 Ending x-coordinate.
 * @param y1 Ending y-coordinate.
 * @param color 4-byte integer representing the color in RGBA format.
 */
void draw_line_incremental(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);

/**
 * @brief Draws a line using the Digital Differential Analyzer (DDA) algorithm
 *
 * Converts the line into evenly spaced points between the two endpoints by
 * incrementing both x and y in small steps. Works well for all slopes.
 *
 * @param x0 Starting x-coordinate
 * @param y0 Starting y-coordinate
 * @param x1 Ending x-coordinate
 * @param y1 Ending y-coordinate
 * @param color 4 byte integer representing the color in RGBA format
 */
void draw_line_dda(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);

/**
 * @brief Draws a straight line using a floating-point decision method.
 *
 * This function draws a line between two points (x0, y0) and (x1, y1)
 * using a floating-point approximation of the line equation y = mx + b.
 *
 * Instead of directly rounding the y-value (as in DDA), it introduces a decision
 * mechanism: for each x, the actual floating-point y position (py) is calculated,
 * and it decides whether to increment the integer y-coordinate based on whether
 * py is closer to y or y + 1.
 *
 * This is a pedagogical step toward Bresenham's algorithm: it avoids rounding
 * and starts thinking in terms of error and decision, though it still uses
 * floating-point math.
 *
 * Horizontal, vertical, and diagonal lines are handled by a separate helper
 * (`handle_basic_lines`) for optimization and clarity.
 *
 * @note This method is slower than integer-only methods, but is useful for
 * understanding how decision-based line drawing works.
 *
 * @param x0 Starting x-coordinate.
 * @param y0 Starting y-coordinate.
 * @param x1 Ending x-coordinate.
 * @param y1 Ending y-coordinate.
 * @param color 4-byte integer representing the color in RGBA format.
 */
void draw_line_midpoint(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);

/**
 * @brief Draws a line using Bresenham’s line drawing algorithm
 *
 * Efficiently draws lines using integer math only. Currently handles lines with
 * slope between 0 and 1 in the positive direction.
 *
 * @todo Extend support for all octants and negative slopes
 *
 * @param x0 Starting x-coordinate
 * @param y0 Starting y-coordinate
 * @param x1 Ending x-coordinate
 * @param y1 Ending y-coordinate
 * @param color 4 byte integer representing the color in RGBA format
 */
void draw_line_bresenham(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);

// TODO: Add description
void draw_line_xiaolin(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);

// TODO: Add description
void draw_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t thickness, uint32_t color);
