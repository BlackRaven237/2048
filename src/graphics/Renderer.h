#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <string>
#include "Font.h"
#include "../utils/Color.h"

class Renderer
{
    SDL_Renderer* mRenderer;
public:
    bool SetRenderDrawColor(Color color);
    bool CreateRenderer(SDL_Window* window);
    void DestroyRenderer();
    void Clear();
    void Present();
    SDL_Renderer* GetRenderer() const { return mRenderer; };
};

void RenderText(SDL_Renderer* renderer, const std::string& text, float x, float y, Color color);
TTF_Font* font();

#endif