#include <renderer.h>

int main(void)
{
    pixmap_clear(BLACK);
    draw_line(100, 100, 200, 200, BLACK);
    pixmap_export();
}
