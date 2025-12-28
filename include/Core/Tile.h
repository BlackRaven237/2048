#pragma once
#include "Color.h"
#include <random>

struct Coord2D {
    float x;
    float y;
    Coord2D(float xValue = 0.0f, float yValue = 0.0f) : x(xValue), y(yValue) {}
};

enum class TileType {
    CELL,
    TILE
};

class Tile {
    int mIndex;
    bool mIsOccupied;
    float size;
    
    std::mt19937 mRandomGenerator;
public:
    Coord2D position;
    Color color;
    Tile(int index, float size);
    Tile(const Tile& other);

    void Move(float deltaTime);
    void Update(float deltaTime);
    void Render();
private:
    int GenerateRandomIndex();
};