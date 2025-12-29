#include "Graphics/Window.h"

Window::Window(const std::string& title, float width, float height) : 
    mTitle(title), mWidth(width), mHeight(height), 
    mIsInitialized(false), mWindow(nullptr), mRenderer(nullptr){}

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

    mRenderer = SDL_CreateRenderer(mWindow, nullptr);
    if(!mRenderer) {
        SDL_Log("Renderer couldn't created: %s\n", SDL_GetError());
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        return false;
    }

    mIsInitialized = true;
    SDL_Log("Window has been successfully initialized");
    return true;
}

void Window::ShutDown() {
    if (mRenderer) {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }

    if (mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }

    SDL_Quit();
    mIsInitialized = false;
    SDL_Log("Window has successfully been closed");
}

void Window::Clear() {
    if (mRenderer) {
        SDL_RenderClear(mRenderer);
    }
}

void Window::Present() {
    if (mRenderer) {
        SDL_RenderPresent(mRenderer);
    }
}

SDL_Renderer* Window::GetRenderer() {
    return mRenderer;
}