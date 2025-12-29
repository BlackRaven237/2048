#pragma once
#include "Color.h"
#include <random>
#include <SDL3/SDL.h>
#include <iostream>

struct Coord2D {
    float x;
    float y;
    Coord2D(float xValue = 0.0f, float yValue = 0.0f) : x(xValue), y(yValue) {}
};

enum class TileType {
    CELL,
    TILE
};

enum class Key {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Tile {
    int mIndex;
    bool mIsOccupied;
    std::mt19937 mRandomGenerator;
    
public:
    Coord2D position;
    float size;
    Color color;

    Tile(int index, float size);
    Tile(const Tile& other);

    void Move(Key key);
    void Update();

    void Render(SDL_Renderer* renderer);
private:
    int GenerateRandomIndex();
};