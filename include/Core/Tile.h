#ifndef TILE_H
#define TILE_H

#include "Cell.h"
#include "Graphics\Window.h"

class Tile {
    int m_value;
public: 
    Vector2D position;
    int row;
    int column;
    float size;
    Color color;

    Tile(Vector2D pos, int row, int column, float size);
    Tile(const Tile& other);

    void Initialize();
    void Move(Vector2D targetPosition, float deltaTime);
    void Render(SDL_Renderer* renderer);
    //void RenderValue(Window& window, SDL_Renderer* renderer);
    
    int GetTileValue() const { return m_value; }
};

#endif