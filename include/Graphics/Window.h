#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "Font.h"
#include "Renderer.h"

class Window {
    std::string mTitle;
    float mWidth;
    float mHeight;
    SDL_Window* mWindow;
    Renderer* mRenderer;
    Font* mFont;
    bool mIsInitialized;

public:
    Window(const std::string& title, float width, float height);
    ~Window();

    bool Initialize();
    void Clear();
    void Present();

    SDL_Window* GetWindow() const;
    SDL_Renderer* GetRenderer() const;
    Font* GetFont() const;

    void RenderText(const std::string& text, float x, float y, const Color& color);
};

#endif