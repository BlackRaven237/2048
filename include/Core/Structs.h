#pragma once
#include <cstdint>

// struct Point2D
// {
//     float x;
//     float y;

//     // Default and Params Constructor
//     Point2D(float xValue = 0.0f, float yValue = 0.0f) : x(xValue), y(yValue) {}

//     Point2D operator+(const Point2D& other) { return Point2D(x + other.x, y + other.y); }
// };

struct Color
{
    uint8_t red;
    uint8_t blue;
    uint8_t green;
    uint8_t alpha;

    // Default Constructor (white color)
    Color() : red(255), green(255), blue(255), alpha(255) {}

    // Params Constructor
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : 
        red(r), green(g), blue(b), alpha(a) {}

    // Base Colors
    static Color Red() { return Color(255, 0, 0); }
    static Color Blue() { return Color(0, 0, 255); }
    static Color Green() { return Color(0, 255, 0); }
    static Color Yellow() { return Color(255, 255, 0); }
    static Color Silver() { return Color(192, 192, 192); }
    static Color Black() { return Color(0, 0, 0, 0); }
    static Color TomatoOrange() { return Color(255, 99, 71); }
};