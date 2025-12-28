#pragma once
#include <cstdint>

struct Color
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
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
    static Color LightGray() { return Color(205, 193, 180); }
    static Color Gainsboro() { return Color(220, 220, 220); }
    static Color Black() { return Color(0, 0, 0, 0); }
    static Color TomatoOrange() { return Color(255, 99, 71); }
};