#ifndef CELL_H
#define CELL_H

#include "utils/color.h"
#include "utils/structs.h"
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