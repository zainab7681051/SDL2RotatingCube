#include "screen.h"
int main(int argc, char* argv[]) {
    Screen screen;
    for (int i{ 0 }; i < 100; i++) {
        screen.pixel(rand() % 640,rand() % 480);
    }
    while(true)
    {
        screen.show();
        screen.input();
    }
    return 0;
}
