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
        return false;
    }

    if(!mFont->InitializeFont("assets/fonts/Roboto-Bold.ttf")) {
        SDL_Log("❌ Couldn't load TTF: %s\n", SDL_GetError());
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

Font* Window::GetFont() const {
    return mFont;
}

void Window::RenderText(const std::string& text, float x, float y, const Color& color) {
    if (!mFont->GetFont() || !mRenderer->GetRenderer()) return;

    SDL_Surface* surface = TTF_RenderText_Solid(mFont->GetFont(), text.c_str(), text.length(), 
        {(Uint8)color.red, (Uint8)color.green, (Uint8)color.blue, (Uint8)color.alpha});
        
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer->GetRenderer(), surface);

    if(!texture) {
        SDL_DestroySurface(surface);
        return;
    }

    SDL_FRect dstRect = { x, y, 
        static_cast<float>(surface->w), 
        static_cast<float>(surface->h)
    };

    SDL_RenderTexture(mRenderer->GetRenderer(), texture, NULL, &dstRect);
    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);
}