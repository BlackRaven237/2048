#ifndef TILE_H
#define TILE_H

#include "Cell.h"

class Tile {
    Coord mCoord;
    int mIndex;
public: 
    Point position;
    float size;
    Color color;

    Tile(Point pos, Coord coord, float size);
    Tile(const Tile& other);
    void Update(std::vector<Cell> &cells);
    void Slide(std::vector<Cell> &cells, Key direction);
    void Render(SDL_Renderer* renderer);
    Coord GetCoord() const { return mCoord; }
    int CalculateTileIndex() { return mCoord.row * 4 +  mCoord.column; }
    int GetTileIndex() const { return mIndex; }
private:
    int GenerateRandomIndex();
    bool IsValidMove(int rowValue, int columnValue);
};

#endif