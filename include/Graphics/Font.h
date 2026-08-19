#ifndef FONT_H
#define FONT_H

#include <SDL3_ttf/SDL_ttf.h>
#include "utils/color.h"

class Font {
    TTF_Font* font;
    
public:
    bool InitializeFont(const char* file, float fontSize) {
        if (!TTF_Init()) return false;

        font = TTF_OpenFont(file, fontSize);

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