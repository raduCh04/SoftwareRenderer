#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.141592653589793f // TODO: Add more digits
#endif

typedef enum Color
{
    BLACK = 0xFF000000,
    WHITE = 0xFFFFFFFF,
    RED = 0xFF0000FF,
    GREEN = 0xFF00FF00,
    BLUE = 0xFFFF0000,
} Color;

enum CONST
{
    WIDTH = 800,
    HEIGHT = 600,
    RES = (WIDTH * HEIGHT),
};

typedef struct Point
{
    uint32_t x, y;
} Point;
typedef Point Vec2;


static uint32_t pixmap[RES];

static void pixmap_clear(uint32_t color)
{
    for (int i = 0; i < RES; i++)
    {
        pixmap[i] = color;
    }
}

static void draw_point(uint32_t x, uint32_t y, uint32_t color)
{
    if (x >= WIDTH || y >= HEIGHT)
        return;
    pixmap[y * WIDTH + x] = color;
}

/*
 * NOTE: This approach is not performance-optimal due to the frequent use of
 * floating-point arithmetic and rounding operations.
 *
 * It performs best when |slope| < 1. For steeper slopes or more consistent
 * performance across all directions, consider using the Digital Differential Analyzer (DDA) algorithm.
 */
static void draw_line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color)
{
    if (x0 == x1 && y0 == y1)
    {
        draw_point(x0, y0, color);
        return;
    }

    // Vertical lines
    if (x0 == x1)
    {
        if (y0 > y1)
        {
            uint32_t temp = y0;
            y0 = y1;
            y1 = temp;
        }
        for (int y = y0; y <= y1; y++)
            draw_point(x0, y, color);
        return;
    }

    // General case
    if (x0 > x1)
    {
        uint32_t temp = x0;
        x0 = x1;
        x1 = temp;
    }
    float m = (y1 - y0) / (float)(x1 - x0);
    float b = y0 - m * x0;
    for (int x = x0; x <= x1; x++)
    {
        float y = m * x + b;
        draw_point(x, roundf(y), color);
    }
}

static void draw_line_dda(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color)
{
    // TODO: Implement
}

static void draw_line_bresenham(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color)
{
    // TODO: Implement
}

static void draw_circle_naive(uint32_t cx, uint32_t cy, float r, uint32_t color)
{
    for (float t = 0; t < 2 * M_PI; t += 0.01f)
    {
        int x = roundf(r * cosf(t));
        int y = roundf(r * sinf(t));
        draw_point(cx + x, cy + y, color);
    }
}

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
static void draw_circle(uint32_t cx, uint32_t cy, float r, uint32_t color)
{
    for (float t = (M_PI / 2); t > (M_PI / 4); t -= 0.01f)
    {
        int x = roundf(r * cosf(t));
        int y = roundf(r * sinf(t));
        draw_point(cx + x, cy + y, color);
        draw_point(cx - x, cy + y, color);
        draw_point(cx + x, cy - y, color);
        draw_point(cx - x, cy - y, color);
        draw_point(cx + y, cy + x, color);
        draw_point(cx - y, cy + x, color);
        draw_point(cx + y, cy - x, color);
        draw_point(cx - y, cy - x, color);
    }
}

/*
 * NOTE: This implementation is derived from the implicit equation of a circle:
 * r² = x² + y², rearranged as y = sqrt(r² - x²), where x ∈ [−r, r].
 *
 * While conceptually straightforward, this method is not optimal due to the
 * computational cost of square root operations and rounding.
 */
static void draw_circle_pyth(uint32_t cx, uint32_t cy, float r, uint32_t color)
{
    int x = 0;
    int y = (int)r;
    while (y >= x)
    {
        draw_point(cx + x, cy + y, color);
        draw_point(cx - x, cy + y, color);
        draw_point(cx + x, cy - y, color);
        draw_point(cx - x, cy - y, color);
        draw_point(cx + y, cy + x, color);
        draw_point(cx - y, cy + x, color);
        draw_point(cx + y, cy - x, color);
        draw_point(cx - y, cy - x, color);

        x++;
        y = roundf(sqrtf(r * r - (float)x * x));
    }
}

static void draw_circle_bresenham(uint32_t cx, uint32_t cy, float r, uint32_t color)
{
    // TODO: Implement
}

static void draw_polygon(const Point *points, size_t n, uint32_t color)
{
    if (n < 2)
        return;
    for (size_t i = 0; i < n - 1; i++)
    {
        draw_line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, color);
    }

    draw_line(points[n - 1].x, points[n - 1].y, points[0].x, points[0].y, color);
}

static void pixmap_export()
{
    FILE *data = fopen("pixmap.data", "w");
    if (data != NULL)
    {
        fwrite(pixmap, sizeof(uint32_t), RES, data);
    }
    fclose(data);
}

int main(void)
{
    pixmap_clear(BLACK);
    pixmap_export();
    return 0;
}
