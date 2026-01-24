#include "Graphics/Window.h"

Window::Window(const std::string& title, float width, float height) : 
    mTitle(title), mWidth(width), mHeight(height),
    mWindow(nullptr), mRenderer(new Renderer), mFont(new Font),
    mIsInitialized(false) {}

Window::~Window() {
    if(mFont) {
        mFont->CloseFont();
        delete mFont;
        mFont = nullptr;
    }

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
    }

    if(!mFont->InitializeFont("assets/fonts/Roboto-Bold.ttf")) {
        SDL_Log("❌ Couldn't load TTF: %s\n", SDL_GetError());
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

Font* Window::GetFont() const {
    return mFont;
}

void Window::RenderText(const std::string& text, float x, float y, const Color& color) {
    SDL_Texture* texture = mFont->LoadText(mRenderer->GetRenderer(), text, color);

    if(!texture) {
        SDL_Log("❌ Couldn't load texture %s\n", SDL_GetError());
        return;
    }

    SDL_FRect dstRect = { x, y, 
        static_cast<float>(mFont->GetSurface()->w), 
        static_cast<float>(mFont->GetSurface()->h)
    };

    SDL_RenderTexture(mRenderer->GetRenderer(), texture, NULL, &dstRect);
    mRenderer->Present();

    if(texture) SDL_DestroyTexture(texture);
}