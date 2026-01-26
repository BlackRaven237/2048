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

    Tile(int value, Vector2D pos, int row, int column, float size);
    Tile(const Tile& other);

    void Move(Vector2D targetPosition, float deltaTime);
    void Render(Window* window);
    void RenderValue(Window* window);
    
    int GetValue() const { return m_value; }
    void SetValue(int value) { m_value = value; }

private:
    Color GetTextColor() const {}
};

#endif