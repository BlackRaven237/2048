#include "Core/Cell.h"

Cell::Cell(int row, int column, float size) : 
    mIsOccupied(false), row(row), column(column), 
    size(size), color(Color::LightGray()) {}

void Cell::SetOccupied(bool value) { 
    mIsOccupied = value; 
}

bool Cell::isOccupied() { 
    return mIsOccupied; 
}

void Cell::Render(SDL_Renderer* renderer) {
    SDL_FRect cell = {
        position.x,
        position.y,
        size,
        size
    };

    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 255);
    SDL_RenderFillRect(renderer, &cell);
}
