#include "screen.h"
#include <cmath>

struct Vec3 {
    float x, y, z;
};
struct Connection {
    int a, b;
};
//The function takes a Vec3 object (representing a point in 3D space) and 
// rotates it around the x, y, and z axes by the specified angles
void rotate(Vec3& point, float x=1, float y=1, float z=1)
{
    float rad{x};
    point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
    point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

    rad = y;
    point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
    point.z = - std::sin(rad) * point.x + std::cos(rad) * point.z;

    rad = z;
    point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
    point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;
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

    std::vector<Connection> connections
    {
        { 0,4 }, { 1,5 }, { 2,6 }, { 3,7 },
        { 0,1 }, { 1,2 }, { 2, 3}, { 3,0 },
        { 4,5 }, { 5,6 }, { 6,7 }, { 7,4 }
    };
    Vec3 centerPoint{};
    for (auto& p : points) {
        centerPoint.x += p.x;        
        centerPoint.y += p.y;        
        centerPoint.z += p.z;
    }
    centerPoint.x /= points.size();
    centerPoint.y /= points.size();
    centerPoint.z /= points.size();
    while(true)
    {
        for (auto& p : points) {
            p.x -= centerPoint.x;
            p.y -= centerPoint.y;
            p.z -= centerPoint.z;
            rotate(p, 0.02, 0.01, 0.04);
            p.x += centerPoint.x;
            p.y += centerPoint.y;
            p.z += centerPoint.z;
            screen.pixel(p.x, p.y);
        }
        for (auto& conn : connections) {
            line(screen, points[conn.a].x, 
                points[conn.a].y, 
                points[conn.b].x, 
                points[conn.b].y);
        }
        screen.show();
        screen.clear();
        screen.input();
        SDL_Delay(30);
    }
    return 0;
}
