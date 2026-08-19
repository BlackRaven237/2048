#ifndef CELL_H
#define CELL_H

#include "utils/Color.h"
#include "utils/Vector2D.h"
#include <SDL3/SDL.h>

class Cell {
    bool mIsOccupied;
public:
    int row;
    int column;
    Vector2D position;
    float size;
    Color color;

    Cell(int row, int column, float size);
    void SetOccupied(bool value);
    bool isOccupied();
    void Render(SDL_Renderer* renderer);
};

#endif