#include "Cell.h"

Cell::Cell(int row, int column, float size) : 
    Square(size), mIsOccupied(false), row(row), 
    column(column), color(Color::LightGray()) {}

void Cell::SetOccupied(bool value) { 
    mIsOccupied = value; 
}

bool Cell::isOccupied() { 
    return mIsOccupied; 
}

void Cell::render(SDL_Renderer* renderer) {
    SDL_FRect cell = {
        position.x,
        position.y,
        size,
        size
    };

    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 255);
    SDL_RenderFillRect(renderer, &cell);
}
