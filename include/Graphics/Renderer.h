#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <string>
#include "Font.h"
#include "Helpers/color.h"

class Renderer
{
    SDL_Renderer* mRenderer;
    Font mFont;
public:
    bool SetRenderDrawColor(Color color);
    bool CreateRenderer(SDL_Window* window);
    void DestroyRenderer();
    void Clear();
    void Present();
    SDL_Renderer* GetRenderer() const { return mRenderer; };
    TTF_Font* GetFont() { return mFont.GetFont(); }

};

#endif