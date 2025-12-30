#include "Core/Tile.h"

Tile::Tile(Coord2D pos, int rowValue, int columnValue, float size) : 
        position(pos), row(rowValue), column(columnValue), 
        mIndex(CalculateTileIndex()), size(size), color(Color::Green()) {}

Tile::Tile(const Tile& other) : 
    position(other.position), row(other.row), column(other.column), 
    mIndex(other.mIndex), size(other.size), color(other.color) {}

// void Tile::Update(std::vector<Tile>& cells) {

// }
// bool Tile::IsValidMove() {
//     return row > 0 && row < 3 && column > 0 && column < 3;
// }

void Tile::Move(Key key) {
    switch (key)
    {
        case Key::UP:
            if(row > 0) row--;
            break;
        case Key::DOWN:
            if(row < 3) row++;
            break;
        case Key::LEFT:
            if(column > 0) column--;
            break;
        case Key::RIGHT:
            if(column < 3) column++;
            break;
    }
    mIndex = CalculateTileIndex();
}

int Tile::GenerateRandomIndex() {
    return 10;
}

void Tile::Render(SDL_Renderer* renderer) {
    SDL_FRect tile = {
        position.x,
        position.y,
        size,
        size
    };

    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 255);
    SDL_RenderFillRect(renderer, &tile);
}