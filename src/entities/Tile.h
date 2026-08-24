#ifndef TILE_H
#define TILE_H

#include "Cell.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
// #include "Renderer.h"

class Tile : public Square {
    int m_value;
    float scale = 0.2f;
public: 
    int row;
    int column;

    Tile(int value, Vector2D position, int row, int column, float size);
    Tile(const Tile& other);

    void move(Vector2D targetPosition, float deltaTime);
    void render(SDL_Renderer* renderer);
    
    int GetValue() const { return m_value; }
    void SetValue(int value) { m_value = value; }

private:
    Color GetTextColor() const;
    Color GetColorBasedOnValue() const;

    void renderValue(SDL_Renderer* renderer);
};

#endif