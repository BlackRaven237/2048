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

    int m_AccumulatedScore;
public:
    Grid(Vector2D position, float width);
    void Initialize(int NumberofCells, int NumberofTiles);
    void EmptyGrid();

    void MoveTiles(Key key);
    void Update(float deltaTime);
    void UpdateOccupiedCells();
    void AddNewTile(float size);
    
    void Render(Window* window);
    int GetScore() const { return m_AccumulatedScore; }
private:
    void InitializeCellsPosition();

    Tile* GetTileAt(int row, int column);
    std::vector<Tile*> CollectTiles(const std::vector<Cell>& row);
    std::vector<std::vector<Cell>> Transpose();

    void slideUp();
    void slideDown();
    void slideLeft();
    void slideRight();
};

#endif