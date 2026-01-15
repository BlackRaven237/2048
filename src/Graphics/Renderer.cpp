#include "Graphics/Renderer.h"

Renderer::Renderer(Color color) : mColor(color) {}

bool Renderer::CreateRenderer(SDL_Window* window) {
    mRenderer = SDL_CreateRenderer(window, nullptr);
    if(!mRenderer) { return false; }
    return true;
}

void Renderer::DestroyRenderer() {
    if (mRenderer) {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }
}

void Renderer::Clear() {
    if (mRenderer) {
        SDL_SetRenderDrawColor(mRenderer, mColor.red, mColor.green, mColor.blue, 255);
        SDL_RenderClear(mRenderer);
    }
}

void Renderer::Present() {
    if (mRenderer) {
        SDL_RenderPresent(mRenderer);
    }
}