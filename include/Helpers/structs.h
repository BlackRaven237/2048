#ifndef STRUCTS_H
#define STRUCTS_H
#include <cmath>

enum class Key {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

struct Vector2D {
    float x;
    float y;
    Vector2D(float xValue = 0.0f, float yValue = 0.0f) : x(xValue), y(yValue) {}
    Vector2D(const Vector2D& other) : x(other.x), y(other.y) {}
    Vector2D& operator=(const Vector2D& other) {
        if (this == &other) return *this;
        this->x = other.x;
        this->y = other.y;
        return *this;
    }

    Vector2D operator+(const Vector2D& other) {
        float dx = x + other.x;
        float dy = y + other.y;
        return Vector2D(dx, dy);
    }

    Vector2D operator-(const Vector2D& other) {
        float dx = x - other.x;
        float dy = y - other.y;
        return Vector2D(dx, dy);
    }

    Vector2D operator*(float scalar) {
        return Vector2D(x * scalar, y * scalar);
    }
};

#endif