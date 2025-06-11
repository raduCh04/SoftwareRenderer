/**
 * @file circle.h
 * @author Radu-D. Chira (github.com/RaduCh04)
 * @brief 
 * @version 0.1
 * @date 2025-05-04
 * 
 */
#include <stdint.h>

/**
 * @brief Draws a circle using the naive parametric equation method
 *
 * This version evaluates the full circle using the (x, y) = (r*cos(t), r*sin(t)) formula,
 * for t in [0, 2π], using a small step size for t.
 *
 * @note This method is computationally expensive due to trigonometric and float operations.
 *
 * @param cx x-coordinate of the center
 * @param cy y-coordinate of the center
 * @param r Radius of the circle
 * @param color 4 byte integer representing the color in RGBA format
 */
void draw_circle_equation1(int32_t cx, int32_t cy, int32_t r, uint32_t color);

/**
 * @brief Draws a full circle by symmetry from 1/8th parametric arc
 *
 * Only computes 1/8th of the circle (π/4 to π/2) using parametric equations
 * and mirrors the points to complete the rest of the circle for better performance.
 *
 * @note Still relies on trigonometric functions and float rounding.
 *
 * @note
 * The function expects the radius as a float for consistency with other functions,
 * but internally it is cast to integer for optimized computation.
 *
 * @param cx x-coordinate of the center
 * @param cy y-coordinate of the center
 * @param r Radius of the circle
 * @param color 4 byte integer representing the color in RGBA format
 */
void draw_circle_equation2(int32_t cx, int32_t cy, int32_t r, uint32_t color);

/**
 * @brief Draws a circle using the Pythagorean theorem (x² + y² = r²)
 *
 * For each x from 0 to r, calculates y using the rearranged formula y = sqrt(r² - x²),
 * and plots symmetric points in all 8 octants.
 *
 * @note Slower due to frequent square root operations and rounding.
 *
 * @note
 * The function expects the radius as a float for consistency with other functions,
 * but internally it is cast to integer for optimized computation.
 *
 * @param cx x-coordinate of the center
 * @param cy y-coordinate of the center
 * @param r Radius of the circle
 * @param color 4 byte integer representing the color in RGBA format
 */
void draw_circle_equation3(int32_t cx, int32_t cy, int32_t r, uint32_t color);

// TODO: Add description
void draw_circle_midpoint(int32_t cx, int32_t cy, int32_t r, uint32_t color);

/**
 * @brief Draws a circle using Bresenham's midpoint circle algorithm.
 *
 * This method is an efficient, integer-only implementation of circle drawing. It avoids
 * floating-point operations and trigonometric calculations by using a decision parameter
 * (D) to determine the next pixel to draw while traversing the circle's octants.
 *
 * It exploits the symmetry of circles by calculating one-eighth of the circle and
 * mirroring the results into the other seven octants using horizontal and vertical reflection.
 *
 * Performance-wise, this algorithm is significantly faster than naive trigonometric
 * or parametric approaches, making it ideal for low-level pixel manipulation.
 *
 * @param cx x-coordinate of the circle center
 * @param cy Y-coordinate of the circle center
 * @param r Radius of the circle
 * @param color 4 byte integer representing the color in RGBA format
 *
 * @note
 * The function expects the radius as a float for consistency with other functions,
 * but internally it is cast to integer for optimized computation.
 */
void draw_circle_bresenham(int32_t cx, int32_t cy, int32_t r, uint32_t color);

// TODO: Add description
void draw_circle(int32_t cx, int32_t cy, int32_t r, uint32_t color);

// TODO: Add description
void fill_circle(int32_t cx, int32_t cy, int32_t r, uint32_t color);