#ifndef GRID_H
#define GRID_H

#include "Tile.h"
#include <random>
#include <algorithm>
#include <memory>

class Grid
{
    float mWidth;
    std::vector<std::vector<Cell>> mCells;
    std::vector<Tile> mTiles;
    size_t mMaxTiles;
    Color mColor;
    Point m_position;
public:
    Grid(Point position, float width);
    void Initialize(int NumberofCells, int NumberofTiles);
    void SpawnNewTiles(float size);
    void MoveTiles(Key key);
    void Update();
    void Render(SDL_Renderer* renderer);
private:
    int CalculateCellIndex(int row, int column);
    int GenerateRandomIndex();
    void InitializeCellsPosition(float size, float margin);

    std::vector<Cell> slideRow(const std::vector<Cell>& row);
    void slideUp();
    void slideDown();
    void slideLeft();
    void slideRight();
    void Transpose();
    void Reverse(std::vector<Cell>& row);

    void showCells();
};

#endif