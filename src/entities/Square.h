#pragma once

#include <SDL3/SDL.h>
#include "Color.h"
#include "Vector2D.h"

class Square {
protected:
    float size;
    Vector2D position;
    Color color;
public:
    Square(float size, Vector2D position) : size(size), position(position) {}
    virtual void render(SDL_Renderer* renderer) = 0;
};
