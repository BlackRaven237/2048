#include "Core/Tile.h"

Tile::Tile(Point pos, int row, int column, float size) : 
    mIndex(CalculateTileIndex()), position(pos), 
    tileRow(row), tileColumn(column), 
    size(size), color(Color::Green()) {}

Tile::Tile(const Tile &other) : 
    mIndex(other.mIndex), position(other.position), 
    tileRow(other.tileRow), tileColumn(other.tileColumn),
    size(other.size), color(other.color) {}

void Tile::Slide(std::vector<Cell> &cells, Key direction) {
}


bool Tile::IsValidMove(int row, int column)
{
    return row >= 0 && row < 4 && column >= 0 && column < 4;
}

void Tile::Render(SDL_Renderer *renderer)
{
    SDL_FRect tile = {
        position.x,
        position.y,
        size,
        size};

    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 255);
    SDL_RenderFillRect(renderer, &tile);
}