#pragma once

#include <cmath>
struct Vector2D {
    float x = 0.0f;
    float y = 0.0f;

    Vector2D() {}
    Vector2D(float x, float y) : x(x), y(y) {}
    Vector2D(const Vector2D& other) : x(other.x), y(other.y) {}

    Vector2D operator+(const Vector2D& other) { return Vector2D(x + other.x, y + other.y); }
    Vector2D operator-(const Vector2D& other) { return Vector2D(x - other.x, y - other.y); }
    Vector2D operator*(float scalar) { return Vector2D(x * scalar, y * scalar); }
    Vector2D& operator=(const Vector2D& other) {
        if (this == &other) return *this;
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
};