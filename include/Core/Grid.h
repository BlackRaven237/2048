#ifndef GRID_H
#define GRID_H

#include "Tile.h"
#include <vector>
#include <memory>
#include <utility>
#include <cstdlib>

class Grid {
    float mWidth;
    std::vector<std::vector<Cell>> mCells;
    std::vector<Tile> mTiles;
    size_t mMaxTiles;
    Color m_color;
    Vector2D m_position;
    float cellSize;

public:
    Grid(Vector2D position, float width);
    void Initialize(int NumberofCells, int NumberofTiles);
    void EmptyGrid();

    void MoveTiles(Key key);
    void Update(float deltaTime);
    void UpdateOccupiedCells();
    void SpawnNewTiles(float size);
    
    void Render(Window* window);

private:
    void InitializeCellsPosition();

    Tile* getTileAt(int row, int column);
    std::vector<Tile*> CollectTiles(const std::vector<Cell>& row);
    std::vector<std::vector<Cell>> Transpose();

    void slideUp();
    void slideDown();
    void slideLeft();
    void slideRight();
};

#endif