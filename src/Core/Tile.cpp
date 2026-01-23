#include "Core/Tile.h"

Tile::Tile(Point pos, int row, int column, float size) : 
    mIndex(CalculateTileIndex()), position(pos), 
    row(row), column(column), 
    size(size), color(Color::Green()) {}

Tile::Tile(const Tile &other) : 
    mIndex(other.mIndex), position(other.position), 
    row(other.row), column(other.column),
    size(other.size), color(other.color) {}

void Tile::Move(Point targetPosition, float deltaTime) {
    float speed = 1200.0f;
    position.x += (targetPosition.x - position.x); //* deltaTime * speed;
    position.y += (targetPosition.y - position.y); //* deltaTime * speed;
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