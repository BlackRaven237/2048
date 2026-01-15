#include "Core/Tile.h"

Tile::Tile(Point pos, Coord coord, float size) : 
    mCoord(coord), mIndex(CalculateTileIndex()), 
    position(pos), size(size), color(Color::Green()) {}

Tile::Tile(const Tile &other) : 
    mCoord(other.mCoord), mIndex(other.mIndex), 
    position(other.position), size(other.size), color(other.color) {}

void Tile::Move(std::vector<Cell> &cells, Key key)
{
    int rowValue = mCoord.row, columnValue = mCoord.column;
    while(true) {
    
    switch (key)
    {
    case Key::UP:
        rowValue--;
        break;
    case Key::DOWN:
        rowValue++;
        break;
    case Key::LEFT:
        columnValue--;
        break;
    case Key::RIGHT:
        columnValue++;
        break;
    default: break;
    }
    if(!IsValidMove(rowValue, columnValue)) return;
        
    int nextIndex = rowValue * 4 + columnValue;
    if(cells[nextIndex].GetState()) return;
    mCoord.row = rowValue;
    mCoord.column = columnValue;
    cells[mIndex].ChangeState();
    mIndex = CalculateTileIndex();
    cells[mIndex].ChangeState();
    }
}

void Tile::Update(std::vector<Cell> &cells)
{
    // Move(cells, key);
    position = Point(cells[mIndex].position);
}

bool Tile::IsValidMove(int rowValue, int columnValue)
{
    return rowValue >= 0 && rowValue < 4 && columnValue >= 0 && columnValue < 4;
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