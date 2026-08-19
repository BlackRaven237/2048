#ifndef CELL_H
#define CELL_H

#include "Square.h"

class Cell : Square {
    bool mIsOccupied;
public:
    int row;
    int column;
    Vector2D position;
    Color color;

    Cell(int row, int column, float size);
    void SetOccupied(bool value);
    bool isOccupied();
    void render(SDL_Renderer* renderer);
};

#endif