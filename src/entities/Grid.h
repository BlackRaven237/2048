#ifndef GRID_H
#define GRID_H

#include "Tile.h"
#include "../utils/Enums.h"
#include <vector>
#include <memory>
#include <utility>
#include <random>

class Grid : public Square {
    std::vector<std::vector<Cell>> mCells;
    std::vector<std::unique_ptr<Tile>> mTiles;

    size_t mMaxTiles = 16;
    float cellSize;

    int m_AccumulatedScore = 0;
    mutable std::mt19937 mRandomGenerator;
public:
    Grid(float size, Vector2D position);
    void Initialize();
    bool IsGameOver();
    bool CheckWin();
    void Reset();

    void MoveTiles(Key key);
    void Update(float deltaTime);
    void UpdateOccupiedCells();
    void RemoveDeadTiles();
    void AddNewTile(float size);
    
    void render(SDL_Renderer* renderer) override;
    int GetScore() const { return m_AccumulatedScore; }
private:
    void InitializeCells();
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