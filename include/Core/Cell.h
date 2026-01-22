#ifndef CELL_H
#define CELL_H

#include "Color.h"
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

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

enum class Key {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

class Cell {
    bool mIsOccupied;
public:
    int cellRow;
    int cellColumn;
    Point position;
    float size;
    Color color;

    Cell(int row, int column, float size);
    void SetOccupied(bool value);
    bool GetState();
    void Render(SDL_Renderer* renderer);
};

#endif