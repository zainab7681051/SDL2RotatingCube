#include "screen.h"
#include <cmath>

struct Vec3 {
    float x, y, z;
};

void rotate(Vec3& point, float x=1, float y=1, float z=1)
{
    float radius = 0;
    radius = x;
    point.y = std::cos(radius) * point.y - std::sin(radius) * point.z;
    point.z = std::sin(radius) * point.y + std::cos(radius) * point.z;

    radius = y;
    point.x = std::cos(radius) * point.x + std::sin(radius) * point.z;
    point.z = - std::sin(radius) * point.x + std::cos(radius) * point.z;

    radius = z;
    point.x = std::cos(radius) * point.x - std::sin(radius) * point.y;
    point.y = std::sin(radius) * point.x + std::cos(radius) * point.y;


}
//This function draws a line on a screen using the Bresenham's algorithm
void line(Screen& screen, float x1, float y1, float x2, float y2)
{
    //difference 
    float dx{ x2 - x1 };
    float dy{ y2 - y1 };
    //lenght of difference
    float len = std::sqrt(dx * dx + dy * dy);
    //angle of line using difference
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
    //////////////////////////
    /*
    * //drawing random dots
    for (int i{0}; i < 100; ++i) {
        screen.pixel(rand() % 640,rand() % 480);
    }
    */
    
    //drawing a square
    /*
    line(screen, 100, 100, 200, 100);
    line(screen, 200, 100, 200, 200);
    line(screen, 200, 200, 100, 200);
    line(screen, 100, 200, 100, 100);
    */

   //////////////////////////////
    std::vector<Vec3> points{
        {100,100,100},
        {200,100,100},
        {200,200,100},
        {100,200,100},

        {100,100,200},
        {200,100,200},
        {200,200,200},
        {100,200,200}
    };

    while(true)
    {
        for (auto& p : points) {
            rotate(p, 0.002, 0.001, 0.004);
        }
        for (auto& p : points) {
            screen.pixel(p.x, p.y);
        }
        screen.show();
        screen.clear();
        screen.input();
        SDL_Delay(30);
    }
    return 0;
}
