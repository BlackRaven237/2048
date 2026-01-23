#ifndef TILE_H
#define TILE_H

#include "Cell.h"

class Tile {
    int mIndex;
public: 
    Point position;
    int row;
    int column;
    float size;
    Color color;

    Tile(Point pos, int row, int column, float size);
    Tile(const Tile& other);
    
    void Move(Point targetPosition, float deltaTime);
    void Render(SDL_Renderer* renderer);
    
    int CalculateTileIndex() { return row * 4 +  column; }
    int GetTileIndex() const { return mIndex; }
private:
    bool IsValidMove(int row, int column);
};

#endif