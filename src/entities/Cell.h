#ifndef CELL_H
#define CELL_H

#include "Square.h"

class Cell : public Square {
    bool mIsOccupied = false;
public:
    int row;
    int column;

    Cell(int row, int column, float size, Vector2D position);
    void SetOccupied(bool value);
    bool isOccupied();
    void render(SDL_Renderer* renderer) override;
};

#endif