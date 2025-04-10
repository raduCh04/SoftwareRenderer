#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>

typedef enum Color
{
    BLACK = 0xFF000000,
    WHITE = 0xFFFFFFFF,
    RED   = 0xFF0000FF,
    GREEN = 0xFF00FF00,
    BLUE  = 0xFFFF0000,
} Color;

enum CONST
{
    WIDTH = 800,
    HEIGHT = 600,
    RES = (WIDTH * HEIGHT),
};

#ifndef M_PI
    #define M_PI 3.14f //TODO: Add more digits
#endif

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
    //TODO: Check boundaries
    pixmap[y * WIDTH + x] = color;
}


/*NOTE: Not efficient since too many floating operations and rounding up one value.
        Works best with |slope| < 1
*/
static void draw_line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color)
{
    //TODO: Check if x0, y0 and x1, y1 are the same
    //TODO: Handle other slopes
    //TODO: Handle vertical lines (Division with 0)

    float m = (y1 - y0) / (x1 - x0); 
    float b = y0 - m * x0;
    for (int x = x0; x < x1; x++)
    {
        float y = m * x + b;
        draw_point(x, roundf(y), color); 
    }
}

static void draw_line_dda(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color)
{
    //TODO: Implement
}

static void draw_line_bresenham(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color)
{
    //TODO: Implement
}

/*NOTE: Based on the equation (x(t), y(t)) = (r * cos t, r * sin t),
        where t [PI/4, PI/2] for 1/8 of the circle. Not efficient, because of too many
        too many sin, cos operations and floating point additions and rounding up.
        Also not accurate since we have to choose the delta t (in this case 0.01).
        Can be optimized by creating a lookup table for sin, cos.
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

/*NOTE: Based on the equation r² = x² + y² => y = sqrt(r² - x²), where x [-r, r]. Still not very efficient,
        because of the sqrt and round ups.
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
    //TODO: Implement
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
    draw_line(50, 60, 100, 130, WHITE);
    draw_circle(200, 200, 10, WHITE);
    pixmap_export();
    return 0;
}
