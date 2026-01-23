#ifndef TILE_H
#define TILE_H

#include "Cell.h"

class Tile {
    int mIndex;
public: 
    Vector2D position;
    int row;
    int column;
    float size;
    Color color;

    Tile(Vector2D pos, int row, int column, float size);
    Tile(const Tile& other);
    
    void Move(Vector2D targetPosition, float deltaTime);
    void Render(SDL_Renderer* renderer);
    
    int CalculateTileIndex() { return row * 4 +  column; }
    int GetTileIndex() const { return mIndex; }
private:
    bool IsValidMove(int row, int column);
};

#endif