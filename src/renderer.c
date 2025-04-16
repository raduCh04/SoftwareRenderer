/**
 * @file renderer.c
 * @author Radu-Dumitru Chira (you@domain.com)
 * @version 0.1
 * @date 2025-04-12
 *
 */

#include <renderer.h>
#include <rmath.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

static int32_t pixmap[RES];

static void swapi(int32_t *a, int32_t *b)
{
    int32_t temp = *a;
    *a = *b;
    *b = temp;
}

void pixmap_clear(int32_t color)
{
    for (int32_t i = 0; i < RES; i++)
        pixmap[i] = color;
}

void draw_point(int32_t x, int32_t y, int32_t color)
{
    if (x >= WIDTH || y >= HEIGHT)
        return;
    pixmap[y * WIDTH + x] = color;
}

static void draw_vertical_line(int32_t x, int32_t y0, int32_t y1, int32_t color)
{
    if (y0 == y1)
    {
        draw_point(x, y0, color);
        return;
    }

    if (y0 > y1)
        swap(&y0, &y1);

    for (int32_t y = y0; y < y1; y++)
    {
        draw_point(x, y, color);
    }
}

static void draw_horizontal_line(int32_t x0, int32_t x1, int32_t y, int32_t color)
{
    if (x0 == x1)
    {
        draw_point(x0, y, color);
        return;
    }

    if (x1 > x0)
        swap(&x0, &x1);

    for (int32_t x = x0; x < x1; x++)
        draw_point(x, y, color);
}

/*
 * NOTE: This approach is not performance-optimal due to the frequent use of
 * floating-point arithmetic and rounding operations.
 *
 * It performs best when |slope| < 1. For steeper slopes or more consistent
 * performance across all directions, consider using the Digital Differential Analyzer (DDA) algorithm.
 */
void draw_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color)
{
    if (x0 == x1 && y0 == y1)
    {
        draw_point(x0, y0, color);
        return;
    }

    if (x0 == x1)
    {
        draw_vertical_line(x0, y0, y1, color);
        return;
    }

    if (y0 == y1)
    {
        draw_horizontal_line(x0, x1, y0, color);
        return;
    }

    // General case
    if (x0 > x1)
    {
        int32_t temp = x0;
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

void draw_line_dda(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color)
{
    if (x0 == x1 && y0 == y1)
    {
        draw_point(x0, y0, color);
        return;
    }

    if (x0 == x1)
    {
        draw_vertical_line(x0, y0, y1, color);
        return;
    }

    if (y0 == y1)
    {
        draw_horizontal_line(x0, x1, y0, color);
        return;
    }

    int dx = x1 - x0;
    int dy = y1 - y0;

    int steps = 0;
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;

    float x = (float)x0;
    float y = (float)y0;

    for (int i = 0; i < steps; i++)
    {
        draw_point(roundf(x), roundf(y), color);
        x += x_inc;
        y += y_inc;
    }
}

void draw_line_bresenham(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color)
{
    if (x0 == x1 && y0 == y1)
    {
        draw_point(x0, y0, color);
        return;
    }

    if (x0 == x1)
    {
        draw_vertical_line(x0, y0, y1, color);
        return;
    }

    if (y0 == y1)
    {
        draw_horizontal_line(x0, x1, y0, color);
        return;
    }

    if (x0 > x1)
    {
        int32_t temp = x0;
        x0 = x1;
        x1 = temp;

        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    int32_t dx = x1 - x0;
    int32_t dy = y1 - y0;

    int32_t D = 2 * dy - dx;
    int32_t x = x0;
    int32_t y = y0;
    draw_point(x, y, color);

    while (x < x1)
    {
        x++;
        if (D < 0)
            D += 2 * dy;
        else
        {
            y++;
            D += 2 * (dy - dx);
        }
        draw_point(x, y, color);
    }
}

void draw_circle_naive(int32_t cx, int32_t cy, float r, int32_t color)
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
void draw_circle(int32_t cx, int32_t cy, float r, int32_t color)
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
void draw_circle_pyth(int32_t cx, int32_t cy, float r, int32_t color)
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

void draw_circle_bresenham(int32_t cx, int32_t cy, float r, int32_t color)
{
    // TODO: Implement
}

void draw_polygon(const Point *points, size_t n, int32_t color)
{
    if (n < 2)
        return;
    for (size_t i = 0; i < n - 1; i++)
    {
        draw_line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, color);
    }

    draw_line(points[n - 1].x, points[n - 1].y, points[0].x, points[0].y, color);
}

void pixmap_export()
{
    FILE *data = fopen("pixmap.data", "w");
    if (data != NULL)
    {
        fwrite(pixmap, sizeof(int32_t), RES, data);
    }
    fclose(data);
}
