#pragma once
#include "Color.h"
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

struct Coord2D {
    float x;
    float y;
    Coord2D(float xValue = 0.0f, float yValue = 0.0f) : x(xValue), y(yValue) {}
    Coord2D(const Coord2D& other) : x(other.x), y(other.y) {}
};

enum class Key {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Cell {
    int mIndex;
    bool mIsOccupied;
public:
    Coord2D position;
    float size;
    Color color;

    Cell(int index, float size) : 
        mIndex(index), size(size), 
        color(Color::LightGray()), mIsOccupied(false) {}

    void ChangeState() { mIsOccupied = !mIsOccupied; }
    bool GetState() { return mIsOccupied; }

    void Render(SDL_Renderer* renderer) {
        SDL_FRect cell = {
            position.x,
            position.y,
            size,
            size
        };

        SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 255);
        SDL_RenderFillRect(renderer, &cell);
    }
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
    void Update(std::vector<Cell>& cells, Key key);
    void Move(std::vector<Cell>& cells, Key key);
    void Render(SDL_Renderer* renderer);
    int CalculateTileIndex() { return row * 4 + column; }
    int GetTileIndex() { return mIndex; }
private:
    int GenerateRandomIndex();
    bool IsValidMove(int rowValue, int columnValue);
};