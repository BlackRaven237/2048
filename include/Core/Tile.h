#ifndef TILE_H
#define TILE_H

#include "Cell.h"

class Tile {
    int mIndex;
public: 
    Point position;
    int tileRow;
    int tileColumn;
    float size;
    Color color;

    Tile(Point pos, int row, int column, float size);
    Tile(const Tile& other);

    void Update();
    void Move(Point targetPosition);
    void Render(SDL_Renderer* renderer);
    
    int CalculateTileIndex() { return tileRow * 4 +  tileColumn; }
    int GetTileIndex() const { return mIndex; }
private:
    bool IsValidMove(int row, int column);
};

#endif