#pragma once
#include "Tile.h"
#include <vector>
#include <memory>

class Grid
{
    float mWidth;
    std::vector<Tile> mCells;
    std::vector<std::unique_ptr<Tile>> mTiles;
    Color mColor;
    Coord2D mPosition;

public:
    Grid(Coord2D pos, float width);
    void Initialize(int NumberofCells, int NumberofTiles);
    void MoveTiles(Key key);
    void Update();
    void Render(SDL_Renderer* renderer);

private:
    int CalculateTileIndex(int row, int column);
    void SetCellsPosition(float size, float margin);
};