#include "Core/Tile.h"

Tile::Tile(Vector2D pos, int row, int column, float size) : 
    mIndex(CalculateTileIndex()), position(pos), 
    row(row), column(column), 
    size(size), color(Color::Green()) {}

Tile::Tile(const Tile &other) : 
    mIndex(other.mIndex), position(other.position), 
    row(other.row), column(other.column),
    size(other.size), color(other.color) {}

void Tile::Move(Vector2D targetPosition, float deltaTime) {
    float dx = targetPosition.x - position.x;
    float dy = targetPosition.y - position.y;
    
    float speed = 200.0f;
    position = position + Vector2D(dx, dy); //* deltaTime * speed;//* deltaTime * speed;
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