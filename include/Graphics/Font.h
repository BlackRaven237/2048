#ifndef FONT_H
#define FONT_H

#include <SDL3_ttf/SDL_ttf.h>
#include "Helpers/color.h"

class Font {
    TTF_Font* font;
    SDL_Surface* mSurface;
    SDL_Color mColor;
public:
    bool InitializeFont(const char* file) {
        if (!TTF_Init()) return false;

        font = TTF_OpenFont(file, 256.0f);

        if(!font) return false;
        return true;
    }

    void CloseFont() {
        if(!font) return;
        if(!mSurface) return;

        TTF_CloseFont(font);
        font = nullptr;

        SDL_DestroySurface(mSurface);
        mSurface = nullptr;

        TTF_Quit();
    }

    void SetFontColor(Color color) { 
        mColor = {
            Uint8(color.red),
            Uint8(color.green),
            Uint8(color.blue),
            Uint8(color.alpha), 
        };
    }

    SDL_Texture* LoadText(SDL_Renderer* renderer, const char* text) {
        mSurface = TTF_RenderText_Solid(font, text, 0, mColor);
        SDL_Texture* mSurfaceTexture = SDL_CreateTextureFromSurface(renderer, mSurface);

        if(!mSurfaceTexture) return nullptr;

        return mSurfaceTexture;
    }
};

#endif