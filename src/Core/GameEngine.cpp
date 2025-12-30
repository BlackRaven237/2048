#include "Core/GameEngine.h"
#include <iostream>

GameEngine::GameEngine(const std::string& title, float width, float height)
    :  mWindow(title, width, height, Color::TomatoOrange()),
    mGrid(Coord2D(static_cast<float>(width * 0.25), static_cast<float>(height * 0.1875)), width / 2), 
    mRunning(false) {}

GameEngine::~GameEngine() {
    GameEngine::ShutDown();
}

bool GameEngine::Initialize() {
    if(!mWindow.Initialize()) return false;

    mGrid.Initialize(16, 2);

    mRunning = true;
    std::cout << "GameEngine has been initialized" << std::endl;
    return true;
}

void GameEngine::ShutDown() {
    std::cout << "GameEngine successfully closed" << std::endl;
}

void GameEngine::Run() {
    while(mRunning) {
        GameEngine::HandleEvents();
        GameEngine::Update();
        GameEngine::Render(mWindow.GetRenderer());
        // ~60 FPS
        SDL_Delay(16);
    }
}

void GameEngine::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            mRunning = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            GameEngine::HandleInputs(event.key.key);
            break;
        }
    }
}

void GameEngine::HandleInputs(SDL_Keycode key) {
    switch (key)
    {
    case SDLK_UP:
        Direction = Key::UP;
        break;
    case SDLK_DOWN:
        Direction = Key::DOWN;
        break;
    case SDLK_LEFT:
        Direction = Key::LEFT;
        break;
    case SDLK_RIGHT:
        Direction = Key::RIGHT;
        break;
    }
    mGrid.MoveTiles(Direction);
}

void GameEngine::Update() {
    mGrid.Update();
}

void GameEngine::Render(SDL_Renderer* renderer) {
    mWindow.Clear();
    mGrid.Render(renderer);
    mWindow.Present();
}