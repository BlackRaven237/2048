#include "Graphics/Renderer.h"

bool Renderer::SetRenderDrawColor(Color color) {
    if(mRenderer) {
        SDL_SetRenderDrawColor(mRenderer, color.red, color.green, color.blue, 255);
        return true;
    }
    return false;
}

bool Renderer::CreateRenderer(SDL_Window* window) {
    if(!mFont.InitializeFont("assets/fonts/Roboto-Bold.ttf", 30.0f)) {
        SDL_Log("❌ Couldn't load TTF: %s\n", SDL_GetError());
        if (!mFont.InitializeFont("C:/Windows/Fonts/arial.ttf", 30.0f)) {
            SDL_Log("⚠️ No font found");
        }
        return false;
    }

    mRenderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(mRenderer, 1); // Vsync

    if(!mRenderer) { return false; }
    return true;
}

void Renderer::DestroyRenderer() {
    mFont.CloseFont();
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

void Renderer::RenderText(const std::string& text, float x, float y, const Color& color) {
    if (!mFont.GetFont() || !mRenderer) return;

    SDL_Surface* surface = TTF_RenderText_Solid(mFont.GetFont(), text.c_str(), text.length(), 
        {(Uint8)color.red, (Uint8)color.green, (Uint8)color.blue, (Uint8)color.alpha});
        
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);

    if(!texture) {
        SDL_DestroySurface(surface);
        return;
    }

    SDL_FRect dstRect = { x, y, 
        static_cast<float>(surface->w), 
        static_cast<float>(surface->h)
    };

    SDL_RenderTexture(mRenderer, texture, NULL, &dstRect);
    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);
}