#include "Graphics/Renderer.h"

bool Renderer::SetRenderDrawColor(Color color) {
    if(mRenderer) {
        SDL_SetRenderDrawColor(mRenderer, color.red, color.green, color.blue, 255);
        return true;
    }
    return false;
}

bool Renderer::CreateRenderer(SDL_Window* window) {
    mRenderer = SDL_CreateRenderer(window, nullptr);
    if(!mRenderer) { return false; }
    return true;
}

void Renderer::DestroyRenderer() {
    SDL_DestroyRenderer(mRenderer);
    mRenderer = nullptr;
}

void Renderer::Clear() {
    if (mRenderer) {
        SDL_RenderClear(mRenderer);
    }
}

void Renderer::Present() {
    if (mRenderer) {
        SDL_RenderPresent(mRenderer);
    }
}