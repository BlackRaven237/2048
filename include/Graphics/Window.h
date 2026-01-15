#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "Core/Color.h"
#include "Renderer.h"

class Window {
    std::string mTitle;
    float mWidth;
    float mHeight;
    SDL_Window* mWindow;
    Renderer mRenderer;
    bool mIsInitialized;
public:
    Window(const std::string& title, float width, float height, Color color);
    ~Window();
    bool Initialize();
    void ShutDown();
    void Clear();
    void Present();
    SDL_Renderer* GetRenderer();
};

#endif