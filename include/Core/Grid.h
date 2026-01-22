#ifndef GRID_H
#define GRID_H

#include "Tile.h"
#include <random>
#include <memory>

class Grid
{
    float mWidth;
    std::vector<std::vector<Cell>> mCells;
    std::vector<Tile> mTiles;
    size_t mMaxTiles;
    Color mColor;
    Point m_position;
    std::mt19937 mRandomGenerator;
public:
    Grid(Point pos, float width);
    void Initialize(int NumberofCells, int NumberofTiles);
    void SpawnNewTiles(float size);
    void MoveTiles(Key key);
    void Update();
    void Render(SDL_Renderer* renderer);
private:
    int CalculateCellIndex(int row, int column);
    int GenerateRandomIndex();
    void SetCellsPosition(float size, float margin);
};

#endif