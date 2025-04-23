/**
 * @file renderer.h
 * @author Radu Chira (github.com/raduCh04)
 * @version 0.1
 * @date 2025-04-12
 * 
 * @brief Core 2D rendering routines including line, circle, and polygon drawing.
 * 
 * @note Colors are stored in ARGB format (Alpha, Red, Green, Blue), rather than RGBA.
 * 
 * Each pixel in the `pixmap` is a 32-bit signed integer, where:
 *   - Bits 24–31: Alpha
 *   - Bits 16–23: Red
 *   - Bits 8–15 : Green
 *   - Bits 0–7  : Blue
 */

 #include <stdint.h>

 /**
  * @brief Predefined basic colors
  * 
  */
typedef enum Color
{
    BLACK = 0xFF000000,
    WHITE = 0xFFFFFFFF,
    RED = 0xFF0000FF,
    GREEN = 0xFF00FF00,
    BLUE =  0xFFFF0000,
} Color;

/**
 * @brief Important constants, which can be changed for personal use
 * 
 */
enum CONST
{
    WIDTH = 800,
    HEIGHT = 600,
    RES = (WIDTH * HEIGHT),
};


/**
 * @brief Clears the entire display to a specified color
 * 
 * Fills the entire pixmap with the given color value.
 * 
 * @param color 4 byte integer representing the color in ARGB format
 */
void pixmap_clear(int32_t color);

/**
 * @brief Draws a single pixel on the display
 * 
 * If the coordinates are outside the display boundaries, no action is taken.
 * 
 * @param x x-coordinate of the pixel
 * @param y y-coordinate of the pixel
 * @param color 4 byte integer representing the color in ARGB format
 */
void draw_point(int32_t x, int32_t y, int32_t color);

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
 * @param color 4 byte integer representing the color in ARGB format
 */
void draw_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color);

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
 * @param color 4 byte integer representing the color in ARGB format
 */
void draw_line_dda(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color);

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
 * @param color 4 byte integer representing the color in ARGB format
 */
void draw_line_bresenham(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color);

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
 * @param color 4 byte integer representing the color in ARGB format
 */
void draw_circle_naive(int32_t cx, int32_t cy, float r, int32_t color);

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
 * @param color 4 byte integer representing the color in ARGB format
 */
void draw_circle(int32_t cx, int32_t cy, float r, int32_t color);

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
 * @param color 4 byte integer representing the color in ARGB format
 */
void draw_circle_pyth(int32_t cx, int32_t cy, float r, int32_t color);

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
 * @param color 4 byte integer representing the color in ARGB format
 * 
 * @note
 * The function expects the radius as a float for consistency with other functions,
 * but internally it is cast to integer for optimized computation.
 */
void draw_circle_bresenham(int32_t cx, int32_t cy, float r, int32_t color);

/**
 * @brief Exports the current state of the pixmap to a file
 * 
 * Saves the `pixmap` array to a file named "pixmap.data" in binary format.
 * This can be used to visualize the frame buffer or debug the rendering output.
 */
void pixmap_export();


