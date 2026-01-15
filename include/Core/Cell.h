#ifndef CELL_H
#define CELL_H

#include "Color.h"
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

struct Coord {
    int row;
    int column;
    Coord(int rowValue = 0, int columnValue = 0) : row(rowValue), column(columnValue) {}
    Coord(const Coord& other) : row(other.row), column(other.column) {}
    Coord& operator=(const Coord& other) {
        if (this == &other) return *this;
        this->row = other.row;
        this->column = other.row;
        return *this; 
    }
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

enum class Key {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

class Cell {
    Coord mCoord;
    bool mIsOccupied;
public:
    Point position;
    float size;
    Color color;

    Cell(Coord coord, float size);
    void ChangeState();
    bool GetState();
    void Render(SDL_Renderer* renderer);
};

#endif