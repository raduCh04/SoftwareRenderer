#include <renderer.h>

int main(void)
{
    pixmap_clear(BLACK);
    draw_circle_bresenham(50, 50, 50, WHITE);
    pixmap_export();
}
