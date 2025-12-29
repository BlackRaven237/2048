#include "Core/Tile.h"

Tile::Tile(int index, float size) : mIndex(index), size(size), color(Color::LightGray()) {}

Tile::Tile(const Tile& other) : mIndex(other.mIndex), size(other.size), color(other.color) {}

void Tile::Render(SDL_Renderer* renderer) {
    SDL_FRect cell = {
        position.x,
        position.y,
        size,
        size
    };

    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 255);
    SDL_RenderFillRect(renderer, &cell);
}

int Tile::GenerateRandomIndex() {

}