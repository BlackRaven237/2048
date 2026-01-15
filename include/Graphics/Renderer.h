#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include "Core/Color.h"

class Renderer
{
    SDL_Renderer* mRenderer;
    Color mColor;
public:
    Renderer(Color color);
    bool CreateRenderer(SDL_Window* window);
    void DestroyRenderer();
    void Clear();
    void Present();
    SDL_Renderer* GetRenderer() { return mRenderer; };
};

#endif