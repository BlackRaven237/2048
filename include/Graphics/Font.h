#ifndef FONT_H
#define FONT_H

#include <SDL3_ttf/SDL_ttf.h>
#include "Helpers/color.h"

class Font {
    TTF_Font* font;
    
public:
    bool InitializeFont(const char* file) {
        if (!TTF_Init()) return false;

        font = TTF_OpenFont(file, 30.0f);

        if(!font) return false;
        return true;
    }

    void CloseFont() {
        if(font) {
            TTF_CloseFont(font);
            font = nullptr;
        }

        TTF_Quit();
    }

    TTF_Font* GetFont() const { 
        return font; 
    }
};

#endif