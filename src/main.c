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
    pixmap[y * WIDTH + x] = color;
}


static void draw_line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color)
{
    float m = (y1 - y0) / (x1 - x0);
    float b = y0 - m * x0;
    for (int x = x0; x < x1; x++)
    {
        float y = m * x + b;
        draw_point(x, roundf(y), color);
    }
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
    draw_point(100, 50, WHITE);
    draw_line(10, 10, 200, 200, WHITE);
    pixmap_export();
    return 0;
}
