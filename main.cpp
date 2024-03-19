#include "screen.h"
#include <cmath>

void line(Screen& screen, float x1, float y1, float x2, float y2)
{
    float dx{ x2 - x1 };
    float dy{ y2 - y1 };
    float len = std::sqrt(dx * dx + dy * dy);
    //angle of line
    float angle = std::atan2(dy, dx);
    for (float i{ 0 }; i < len; ++i) 
    {
        screen.pixel(
            x1 + std::cos(angle) * i,
            y1 + std::sinf(angle) * i
        );
    }
}
int main(int argc, char* argv[]) {
    Screen screen;
    for (int i{ 0 }; i < 100; ++i) {
        screen.pixel(rand() % 640,rand() % 480);
    }
    while(true)
    {
        screen.show();
        screen.input();
    }
    return 0;
}
