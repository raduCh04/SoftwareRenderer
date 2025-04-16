#include <renderer.h>

int main(void)
{
    pixmap_clear(BLACK);
    draw_line_bresenham(100, 100, 200, 200, WHITE);
    pixmap_export();
}
