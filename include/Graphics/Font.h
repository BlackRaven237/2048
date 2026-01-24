#ifndef FONT_H
#define FONT_H

#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "Helpers/color.h"

class Font {
    TTF_Font* font;
    SDL_Surface* mSurface;
    SDL_Texture* mSurfaceTexture;

public:
    bool InitializeFont(const char* file) {
        if (!TTF_Init()) return false;

        font = TTF_OpenFont(file, 24.0f);

        if(!font) return false;
        return true;
    }

    void CloseFont() {
        if(!font) return;
        TTF_CloseFont(font);
        font = nullptr;

        if(!mSurface) return;
        SDL_DestroySurface(mSurface);
        mSurface = nullptr;

        if(!mSurfaceTexture) return;
        SDL_DestroyTexture(mSurfaceTexture);
        mSurfaceTexture = nullptr;

        TTF_Quit();
    }

    SDL_Texture* LoadText(SDL_Renderer* renderer, const std::string& text, const Color& color) {
        if (!renderer) return nullptr;

        mSurface = TTF_RenderText_Solid(font, text.c_str(), text.length(), 
            {(Uint8)color.red, (Uint8)color.green, (Uint8)color.blue, (Uint8)color.alpha});
        
        if (!mSurface) return nullptr;
        mSurfaceTexture = SDL_CreateTextureFromSurface(renderer, mSurface);
        SDL_DestroySurface(mSurface);

        if(!mSurfaceTexture) return nullptr;
        return mSurfaceTexture;
    }

    TTF_Font* GetFont() const { return font; }
    SDL_Surface* GetSurface() const { return mSurface; }
    SDL_Texture* GetTexture() const { return mSurfaceTexture; }
};

#endif