#ifndef TILE_H
#define TILE_H

#include "Cell.h"

class Tile {
    int row;
    int column;
    int mIndex;
public: 
    Coord2D position;
    float size;
    Color color;

    Tile(Coord2D pos, int rowValue, int columnValue, float size);
    Tile(const Tile& other);
    void Update(std::vector<Cell>& cells);
    void Move(std::vector<Cell>& cells, Key key);
    void Render(SDL_Renderer* renderer);
    int CalculateTileIndex() { return row * 4 + column; }
    int GetTileIndex() { return mIndex; }
private:
    int GenerateRandomIndex();
    bool IsValidMove(int rowValue, int columnValue);
};

#endif