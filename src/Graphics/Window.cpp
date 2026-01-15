#include "Graphics/Window.h"

Window::Window(const std::string& title, float width, float height, Color color) : 
    mTitle(title), mWidth(width), mHeight(height),
    mWindow(nullptr), mRenderer(color), mIsInitialized(false) {}

Window::~Window() {
    Window::ShutDown();
}

bool Window::Initialize() {
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init() error : %s\n", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
        mTitle.c_str(),
        static_cast<int>(mWidth),
        static_cast<int>(mHeight),
        SDL_WINDOW_RESIZABLE
    );

    if(!mWindow) {
        SDL_Log("Window couldn't created: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    if(!mRenderer.CreateRenderer(mWindow)) {
        SDL_Log("Renderer couldn't created: %s\n", SDL_GetError());
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }

    mIsInitialized = true;
    SDL_Log("Window has been successfully initialized");
    return true;
}

void Window::ShutDown() {
    mRenderer.DestroyRenderer();

    if (mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }

    SDL_Quit();
    mIsInitialized = false;
    SDL_Log("Window has successfully been closed");
}

void Window::Clear() {
    mRenderer.Clear();
}

void Window::Present() {
    mRenderer.Present();
}

SDL_Renderer* Window::GetRenderer() {
    return mRenderer.GetRenderer();
}