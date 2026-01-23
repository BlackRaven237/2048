#ifndef STRUCTS_H
#define STRUCTS_H

enum class Key {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

struct Point {
    float x;
    float y;
    Point(float xValue = 0.0f, float yValue = 0.0f) : x(xValue), y(yValue) {}
    Point(const Point& other) : x(other.x), y(other.y) {}
    Point& operator=(const Point& other) {
        if (this == &other) return *this;
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
};

#endif