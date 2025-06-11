#include <renderer.h>

int main(void)
{
    pixmap_clear(WHITE);
    fill_circle(200, 200, 100, BLUE);
    pixmap_export();
}
