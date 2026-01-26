#ifndef GRID_H
#define GRID_H

#include "Tile.h"
#include <vector>
#include <memory>
#include <utility>
#include <random>

class Grid {
    float mWidth;
    std::vector<std::vector<Cell>> mCells;
    std::vector<std::unique_ptr<Tile>> mTiles;
    size_t mMaxTiles;
    Color m_color;
    Vector2D m_position;
    float cellSize;

    int m_AccumulatedScore;
    mutable std::mt19937 mRandomGenerator;
public:
    Grid(Vector2D position, float width);
    void Initialize(int NumberofCells, int NumberofTiles);
    void Clear();

    void MoveTiles(Key key);
    void Update(float deltaTime);
    void UpdateOccupiedCells();
    void RemoveDeadTiles();
    void AddNewTile(float size);
    
    void Render(Window* window);
    int GetScore() const { return m_AccumulatedScore; }
private:
    void InitializeCellsPosition();

    Tile* GetTileAt(int row, int column);
    bool Merge(std::vector<Tile*>& row);
    std::vector<Tile*> Compressed(const std::vector<Cell>& row);
    std::vector<std::vector<Cell>> Transpose();

    bool slideUp();
    bool slideDown();
    bool slideLeft();
    bool slideRight();
};

#endif