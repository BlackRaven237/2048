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
    float cellSize;
public:
    Grid(Point position, float width);
    void Initialize(int NumberofCells, int NumberofTiles);
    void SpawnNewTiles(float size);
    void MoveTiles(Key key);
    void Update(float deltaTime);
    void Clear();
    void Render(SDL_Renderer* renderer);

private:
    int GenerateRandomIndex();
    void InitializeCellsPosition();

    Tile* getTileAt(int row, int column);
    std::vector<Tile*> CollectTiles(const std::vector<Cell>& row);
    std::vector<std::vector<Cell>> Transpose();
    void showCells();

    void slideUp();
    void slideDown();
    void slideLeft();
    void slideRight();
};

#endif