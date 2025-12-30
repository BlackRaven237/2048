#pragma once
#include "Tile.h"
#include <vector>
#include <random>
#include <memory>

class Grid
{
    float mWidth;
    std::vector<Cell> mCells;
    std::vector<Tile> mTiles;
    Color mColor;
    Coord2D mPosition;
    std::mt19937 mRandomGenerator;
public:
    Grid(Coord2D pos, float width);
    void Initialize(int NumberofCells, int NumberofTiles);
    void MoveTiles(Key key);
    void Update();
    void Render(SDL_Renderer* renderer);

private:
    int CalculateCellIndex(int row, int column);
    int GenerateRandomIndex();
    void SetCellsPosition(float size, float margin);
};