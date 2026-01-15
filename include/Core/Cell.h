#ifndef CELL_H
#define CELL_H

#include "Color.h"
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

struct Coord2D {
    float x;
    float y;
    Coord2D(float xValue = 0.0f, float yValue = 0.0f) : x(xValue), y(yValue) {}
    Coord2D(const Coord2D& other) : x(other.x), y(other.y) {}
    Coord2D operator=(const Coord2D& other) { return Coord2D(other); }
};

enum class Key {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

class Cell {
    int mIndex;
    bool mIsOccupied;
public:
    Coord2D position;
    float size;
    Color color;

    Cell(int index, float size);
    void ChangeState();
    bool GetState();
    void Render(SDL_Renderer* renderer);
};

#endif