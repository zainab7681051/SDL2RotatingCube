#include "screen.h"
#include <cmath>
#include <iostream>
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

std::ostream& operator<<(std::ostream& o, const Vec3& v) {
    return o << v.x<<"\t\t"<<v.y<<"\t\t"<<v.z<<"\n";
}

int main(int argc, char* argv[]) {
    Screen screen;

    // Initialization of points vector to define the vertices of the cube
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

    //connections between the edges of the cube
    std::vector<Connection> connections
    {
        { 0,4 }, { 1,5 }, { 2,6 }, { 3,7 },
        { 0,1 }, { 1,2 }, { 2, 3}, { 3,0 },
        { 4,5 }, { 5,6 }, { 6,7 }, { 7,4 }
    };

    // Calculation of the center point of the cube using the points vector
    Vec3 centerPoint{};
    for (auto& p : points) {
        centerPoint.x += p.x;        
        centerPoint.y += p.y;        
        centerPoint.z += p.z;
    }
    centerPoint.x /= points.size();
    centerPoint.y /= points.size();
    centerPoint.z /= points.size();

    const float xAngle{ 0.02f }, yAngle{ 0.01f }, zAngle{ 0.04f };

    while (true) {

        for (auto& p : points) {
            p.x -= centerPoint.x;
            p.y -= centerPoint.y;
            p.z -= centerPoint.z;
            rotate(p, xAngle, yAngle, zAngle);
            p.x += centerPoint.x;
            p.y += centerPoint.y;
            p.z += centerPoint.z;
            std::cout << p;
            screen.pixel(p.x, p.y);
        }

        for (auto& conn : connections) {
            line(screen, points[conn.a].x,
                points[conn.a].y,
                points[conn.b].x,
                points[conn.b].y);
        }
        //for (auto& p : points) {
        //    std::cout << p;
        //}
        screen.show();
        screen.clear();
        screen.input();
        SDL_Delay(30);
    }
    return 0;
}
