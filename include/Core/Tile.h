#ifndef TILE_H
#define TILE_H

#include "Color.h"
#include "Cell.h"
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

struct Coord2D {
    float x;
    float y;
    Coord2D(float xValue = 0.0f, float yValue = 0.0f) : x(xValue), y(yValue) {}
    Coord2D(const Coord2D& other) : x(other.x), y(other.y) {}
    Coord2D operator=(const Coord2D& other) { return Coord2D(other); }
};

enum class Key {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

class Tile {
    int row;
    int column;
    int mIndex;
public: 
    Coord2D position;
    float size;
    Color color;

    Tile(Coord2D pos, int rowValue, int columnValue, float size);
    Tile(const Tile& other);
    void Update(std::vector<Cell>& cells);
    void Move(std::vector<Cell>& cells, Key key);
    void Render(SDL_Renderer* renderer);
    int CalculateTileIndex() { return row * 4 + column; }
    int GetTileIndex() { return mIndex; }
private:
    int GenerateRandomIndex();
    bool IsValidMove(int rowValue, int columnValue);
};

#endif