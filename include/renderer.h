/**
 * @file renderer.h
 * @author Radu Chira (you@domain.com)
 * @version 0.1
 * @date 2025-04-12
 * 
 */

 #include <stdint.h>

typedef enum Color
{
    BLACK = 0xFF000000,
    WHITE = 0xFFFFFFFF,
    RED = 0xFF0000FF,
    GREEN = 0xFF00FF00,
    BLUE =  0xFFFF0000,
} Color;

enum CONST
{
    WIDTH = 800,
    HEIGHT = 600,
    RES = (WIDTH * HEIGHT),
};

void pixmap_clear(uint32_t color);
void draw_point(uint32_t x, uint32_t y, uint32_t color);

/*
 * NOTE: This approach is not performance-optimal due to the frequent use of
 * floating-point arithmetic and rounding operations.
 *
 * It performs best when |slope| < 1. For steeper slopes or more consistent
 * performance across all directions, consider using the Digital Differential Analyzer (DDA) algorithm.
 */
void draw_line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color);

void draw_line_dda(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color);

void draw_line_bresenham(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color);

void draw_circle_naive(uint32_t cx, uint32_t cy, float r, uint32_t color);

/*
 * NOTE: This implementation is based on the parametric equation
 * (x(t), y(t)) = (r * cos(t), r * sin(t)), where t ∈ [π/4, π/2],
 * representing 1/8 of a circle.
 *
 * This approach is inefficient due to the high number of trigonometric
 * function calls (sin, cos), floating-point arithmetic, and rounding operations.
 * Additionally, accuracy is limited by the choice of the time step (e.g., Δt = 0.01).
 *
 * Performance and precision can be significantly improved by using a
 * precomputed lookup table for sine and cosine values.
 */
void draw_circle(uint32_t cx, uint32_t cy, float r, uint32_t color);

/*
 * NOTE: This implementation is derived from the implicit equation of a circle:
 * r² = x² + y², rearranged as y = sqrt(r² - x²), where x ∈ [−r, r].
 *
 * While conceptually straightforward, this method is not optimal due to the
 * computational cost of square root operations and rounding.
 */
void draw_circle_pyth(uint32_t cx, uint32_t cy, float r, uint32_t color);

void draw_circle_bresenham(uint32_t cx, uint32_t cy, float r, uint32_t color);

void pixmap_export();


