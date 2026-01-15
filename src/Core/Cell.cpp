#include "Core/Cell.h"

Cell::Cell(int index, float size) : 
    mIndex(index), mIsOccupied(false), 
    size(size), color(Color::LightGray()) {}

void Cell::ChangeState() { 
    mIsOccupied = !mIsOccupied; 
}

bool Cell::GetState() { 
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
