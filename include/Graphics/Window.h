#pragma once
#include <SDL3/SDL.h>
#include <string>
#include "include/Core/Color.h"

class Window {
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    std::string mTitle;
    float mWidth;
    float mHeight;
    bool mIsInitialized;
public:
    Window(const std::string& title, float width, float height);
    ~Window();
    bool Initialize();
    void ShutDown();
    void Clear();
    void Present();
};