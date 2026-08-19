#ifndef TILE_H
#define TILE_H

#include "Cell.h"
#include <SDL3/SDL.h>
#include "Graphics/Renderer.h"

class Tile {
    int m_value;
public: 
    Vector2D position;
    int row;
    int column;
    float size;
    float scale = 0.2f;
    Color color;

    Tile(int value, Vector2D pos, int row, int column, float size);
    Tile(const Tile& other);

    void Move(Vector2D targetPosition, float deltaTime);
    void Render(Renderer* renderer);
    void RenderValue(Renderer* renderer);
    
    int GetValue() const { return m_value; }
    void SetValue(int value) { m_value = value; }

private:
    Color GetTextColor() const;
    Color GetColorBasedOnValue() const;
};

#endif