#pragma once
#include "Tile.h"
#include <vector>
#include <memory>

class Grid {
    float mWidth;
    float mHeight;
    std::vector<Tile> mCells;
    std::vector<std::unique_ptr<Tile>> mTiles;
    Color mColor;
public:
    Grid(float width, float height, Color color = Color::Gainsboro()) : mWidth(width), mHeight(height) {}

    bool Initialize();
    void Update();
    void Render(); 
};