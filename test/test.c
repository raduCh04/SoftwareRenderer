#include <renderer.h>

int main(void)
{
    pixmap_clear(BLACK);
    // draw_point(100, 100, WHITE);
    // draw_point_thick(300, 300, 4, RED);
    draw_line_bresenham(50, 160, 200, 200, BLUE);
    pixmap_export();
}
