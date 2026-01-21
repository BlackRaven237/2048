#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "Renderer.h"

class Window {
    std::string mTitle;
    float mWidth;
    float mHeight;
    SDL_Window* mWindow;
    Renderer* mRenderer;
    bool mIsInitialized;
public:
    Window(const std::string& title, float width, float height);
    ~Window();
    bool Initialize();
    void Clear();
    void Present();
    SDL_Renderer* GetRenderer();
};

#endif