#pragma once

#include <SDL3/SDL.h>
#include "Color.h"
#include "Vector2D.h"

class Square {
protected:
    float size;
public:
    Square(float size) { this->size = size; }
    virtual void render(SDL_Renderer* renderer) = 0;
};
