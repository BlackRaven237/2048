#include "Graphics/Window.h"

Window::Window(const std::string& title, float width, float height) : 
    mTitle(title), mWidth(width), mHeight(height),
    mWindow(nullptr), mRenderer(new Renderer),
    mIsInitialized(false) {}

Window::~Window() {
    if (mRenderer) {
        mRenderer->DestroyRenderer();
        delete mRenderer;
        mRenderer = nullptr;
    }

    if (mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }

    SDL_Quit();
    mIsInitialized = false;
    SDL_Log("✅ Window successfully closed");
}

bool Window::Initialize() {
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("❌ SDL_Init() error : %s\n", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
        mTitle.c_str(),
        static_cast<int>(mWidth),
        static_cast<int>(mHeight),
        SDL_WINDOW_RESIZABLE
    );

    if(!mWindow) {
        SDL_Log("❌ Couldn't create window: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    if(!mRenderer->CreateRenderer(mWindow)) {
        SDL_Log("❌ Couldn't create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        return false;
    }

    mIsInitialized = true;
    SDL_Log("✅ Window successfully initialized");
    return true;
}

void Window::Clear() {
    mRenderer->SetRenderDrawColor(Color::TomatoOrange());
    mRenderer->Clear();
}

void Window::Present() {
    mRenderer->Present();
}

SDL_Window* Window::GetWindow() const {
    return mWindow;
}

SDL_Renderer* Window::GetRenderer() const {
    return mRenderer->GetRenderer();
}
