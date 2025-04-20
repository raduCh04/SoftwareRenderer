/**
 * @file renderer.c
 * @author Radu-Dumitru Chira (you@domain.com)
 * @version 0.1
 * @date 2025-04-12
 */

#include <renderer.h>
#include <rmath.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Emulates a display
 * 
 */
static int32_t pixmap[RES]; 

/**
 * @brief Swaps two integers
 * 
 * @param a Pointer to integer a
 * @param b Pointer to integer b
 */
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

/**
 * @brief Draws a vertical line at a specified x-coordinate between two y-coordinates
 * 
 * This function draws a vertical line segment by plotting individual points
 * from y0 to y1 (exclusive). If y0 > y1, they are swapped to maintain drawing order.
 * 
 * @param x x-axis coordinate where the vertical line is drawn
 * @param y0 starting y-coordinate
 * @param y1 ending y-coordinate
 * @param color 4 byte integer which represents a color (ARGB)
 */
static void draw_vertical_line(int32_t x, int32_t y0, int32_t y1, int32_t color)
{
    if (y0 == y1)
    {
        draw_point(x, y0, color);
        return;
    }

    if (y0 > y1)
        swapi(&y0, &y1);

    for (int32_t y = y0; y < y1; y++)
    {
        draw_point(x, y, color);
    }
}

/**
 * @brief Draws a horizontal line at a specified y-coordinate between two x-coordinates
 * 
 * This function draws a horizontal line segment by plotting individual points
 * from x0 to x1 (exclusive). If x1 > x0, they are swapped to maintain drawing order.
 * 
 * @param x0 starting x-coordinate
 * @param x1 ending x-coordinate
 * @param y y-axis coordinate where the horizontal line is drawn
 * @param color 4 byte integer which represents a color (ARGB)
 */
static void draw_horizontal_line(int32_t x0, int32_t x1, int32_t y, int32_t color)
{
    if (x0 == x1)
    {
        draw_point(x0, y, color);
        return;
    }

    if (x1 > x0)
        swapi(&x0, &x1);

    for (int32_t x = x0; x < x1; x++)
        draw_point(x, y, color);
}

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

//TODO: Handle other slopes (m < 0, m > 0)
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
    int32_t incrEast = 2 * dy;
    int32_t incrNEast = 2 * (dy - dx);
    int32_t x = x0;
    int32_t y = y0;

    draw_point(x, y, color);

    while (x < x1)
    {
        x++;
        if (D < 0)
            D += incrEast;
        else
        {
            y++;
            D += incrNEast;
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

void pixmap_export(void)
{
    FILE *data = fopen("pixmap.data", "w");
    if (data != NULL)
    {
        fwrite(pixmap, sizeof(int32_t), RES, data);
    }
    fclose(data);
}
