/**
 * @file renderer.c
 * @author Radu-Dumitru Chira (github.com/RaduCh04)
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
#include <assert.h>

/**
 * @brief Emulates a display
 *
 */
static uint32_t pixmap[RES];

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

void pixmap_clear(uint32_t color)
{
    for (uint32_t i = 0; i < RES; i++)
        pixmap[i] = color;
}

void pixmap_export(void)
{
    FILE *data = fopen("pixmap.ppm", "w");
    if (data != NULL)
    {
        fprintf(data, "P3\n%d %d\n255\n", WIDTH, HEIGHT);
        for (uint32_t i = 0; i < RES; i++)
        {
            uint32_t pixel = pixmap[i];

            uint8_t r = (pixel >> 24) & 0xFF;
            uint8_t g = (pixel >> 16) & 0xFF;
            uint8_t b = (pixel >> 8) & 0xFF;
            uint8_t a = (pixel >> 0) & 0xFF; // If needed in future

            fprintf(data, "%d %d %d ", r, g, b);

            if ((i + 1) % WIDTH == 0)
                fprintf(data, "\n");
        }
    }
    fclose(data);
}

void draw_point(int32_t x, int32_t y, uint32_t color)
{
    if (x >= WIDTH || y >= HEIGHT || y < 0 || x < 0) // TODO: Negative coordinates?
        return;
    pixmap[y * WIDTH + x] = color;
}

void draw_point_thick(int32_t x, int32_t y, int32_t thickness, uint32_t color)
{
    int32_t radius = thickness / 2;
    for (int32_t dx = -radius; dx <= radius; dx++)
        for (int32_t dy = -radius; dy <= radius; dy++)
        {
            draw_point(x + dx, y + dy, color);
        }
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
 * @param color 4 byte integer which represents a color (RGBA)
 */
static void draw_vertical_line(int32_t x, int32_t y0, int32_t y1, uint32_t color)
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
 * @param color 4 byte integer which represents a color (RGBA)
 */
static void draw_horizontal_line(int32_t x0, int32_t x1, int32_t y, uint32_t color)
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

// TODO: Add description
static bool handle_basic_lines(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color) //TODO: Add thickness?
{
    if (x0 == x1 && y0 == y1)
    {
        draw_point(x0, y0, color);
        return true;
    }

    if (x0 == x1)
    {
        draw_vertical_line(x0, y0, y1, color);
        return true;
    }

    if (y0 == y1)
    {
        draw_horizontal_line(x0, x1, y0, color);
        return true;
    }

    return false;
}

void draw_line_equation(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
{

    if (handle_basic_lines(x0, y0, x1, y1, color))
        return;

    bool steep = abs(y1 - y0) > abs(x1 - x0);

    if (steep) // Handle steep slope
    {
        swapi(&x0, &y0);
        swapi(&x1, &y1);
    }

    if (x0 > x1) // Draw from "left" to "right"
    {
        swapi(&x0, &x1);
        swapi(&y0, &y1);
    }

    float m = (float)(y1 - y0) / (x1 - x0);
    float b = y0 - m * x0;
    for (int32_t x = x0; x <= x1; x++) // TODO: Check if inclusive or exclusive
    {
        float y = m * x + b;
        draw_point(x, roundf(y), color);
    }
}

void draw_line_incremental(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
{
    if (handle_basic_lines(x0, y0, x1, y1, color))
        return;

    bool steep = abs(y1 - y0) > abs(x1 - x0);

    if (steep) // Handle steep slopes
    {
        swapi(&x0, &y0);
        swapi(&x1, &y1);
    }

    if (x0 > x1) // Draw from "left" to "right"
    {
        swapi(&x0, &x1);
        swapi(&y0, &y1);
    }

    float m = (y1 - y0) / (float)(x1 - x0);
    float b = y0 - m * x0;
    float y = m * x0 + b;
    for (int32_t x = x0; x <= x1; x++) // TODO: Check if inclusive or exclusive
    {
        y += m;
        draw_point(x, roundf(y), color);
    }
}

void draw_line_dda(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
{
    if (handle_basic_lines(x0, y0, x1, y1, color))
        return;

    int32_t dx = x1 - x0;
    int32_t dy = y1 - y0;

    int32_t steps = 0;
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;

    float x = (float)x0;
    float y = (float)y0;

    for (int32_t i = 0; i < steps; i++)
    {
        draw_point(roundf(x), roundf(y), color);
        x += x_inc;
        y += y_inc;
    }
}

void draw_line_midpoint(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
{
    if (handle_basic_lines(x0, y0, x1, y1, color))
        return;

    if (x0 > x1)
    {
        swapi(&x0, &x1);
        swapi(&y0, &y1);
    }

    float m = (float)(y1 - y0) / (x1 - x0);
    float b = y0 - m * x0;
    int32_t y = y0;

    for (int32_t x = x0; x <= x1; x++)
    {
        float py = m * x + b;
        if (py > y + 0.5f)
            y++;

        draw_point(x, y, color);
    }
}

// TODO: Handle other slopes (m < 0, m > 1)
void draw_line_bresenham(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
{
    if (handle_basic_lines(x0, y0, x1, y1, color))
        return;

    if (x0 > x1)
    {
        swapi(&x0, &x1);
        swapi(&y0, &y1);
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

void draw_line_xiaolin(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
{
    assert(false);
    // TODO: Implement
}

void draw_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t thickness, uint32_t color)
{
    assert(false);
    // TODO: Implement
}

static void draw_circle_symmetric(int32_t cx, int32_t cy, int32_t x, int32_t y, uint32_t color)
{
    draw_point(cx + x, cy + y, color);
    draw_point(cx - x, cy + y, color);
    draw_point(cx + x, cy - y, color);
    draw_point(cx - x, cy - y, color);
    draw_point(cx + y, cy + x, color);
    draw_point(cx - y, cy + x, color);
    draw_point(cx + y, cy - x, color);
    draw_point(cx - y, cy - x, color);
}

void draw_circle_equation1(int32_t cx, int32_t cy, int32_t r, uint32_t color) // TODO: Add t parameter?
{
    for (float t = 0; t < 2 * M_PI; t += 0.01f)
    {
        int32_t x = roundf(r * cosf(t));
        int32_t y = roundf(r * sinf(t));
        draw_point(cx + x, cy + y, color);
    }
}

void draw_circle_equation2(int32_t cx, int32_t cy, int32_t r, uint32_t color) // TODO: Add t parameter?
{
    for (float t = (M_PI / 2); t > (M_PI / 4); t -= 0.01f)
    {
        int32_t x = roundf(r * cosf(t));
        int32_t y = roundf(r * sinf(t));
        draw_circle_symmetric(cx, cy, x, y, color);
    }
}

void draw_circle_equation3(int32_t cx, int32_t cy, int32_t r, uint32_t color)
{
    int32_t x = 0;
    int32_t y = r;

    while (y >= x)
    {
        draw_circle_symmetric(cx, cy, x, y, color);
        x++;
        y = roundf(sqrtf(r * r - (float)x * x));
    }
}

void draw_circle_midpoint(int32_t cx, int32_t cy, int32_t r, uint32_t color)
{
    // TODO: Implement
    assert(false);
}

void draw_circle_bresenham(int32_t cx, int32_t cy, int32_t r, uint32_t color)
{
    int32_t r2 = r + r;
    int32_t x = r;
    int32_t y = 0;
    int32_t dy = -2;
    int32_t dx = r2 + r2 - 4;
    int32_t D = r2 - 1;

    while (y <= x)
    {
        draw_circle_symmetric(cx, cy, x, y, color);

        D += dy;
        dy -= 4;
        y++;

        if (D < 0)
        {
            D += dx;
            dx -= 4;
            x--;
        }
    }
}

void draw_circle(int32_t cx, int32_t cy, int32_t r, uint32_t color)
{
    // TODO: Implement
    assert(false);
}

void fill_circle(int32_t cx, int32_t cy, int32_t r, uint32_t color)
{
    // TODO: Implement
    assert(false);
}
