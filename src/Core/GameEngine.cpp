#include "Core\GameEngine.h"

GameEngine::GameEngine(const std::string& title, float width, float height) : 
    mWindow(title, width, height),
    mGrid(Point(static_cast<float>(width * 0.25), static_cast<float>(height * 0.1875)), width / 2), 
    Direction(Key::NONE), IsKeyPressed(false), mRunning(false) {}

GameEngine::~GameEngine() {
    GameEngine::ShutDown();
}

bool GameEngine::Initialize() {
    if(!mWindow.Initialize()) return false;

    mGrid.Initialize(4, 2);

    mRunning = true;
    std::cout << "GameEngine has been initialized" << std::endl;
    return true;
}

void GameEngine::ShutDown() {
    std::cout << "GameEngine successfully closed" << std::endl;
}

void GameEngine::Run() {
    Uint64 LastUpdateTime = 0, frames = 0;
    while(mRunning) {
        Uint64 CurrentTime = SDL_GetTicks();

        GameEngine::HandleEvents();

        // elasped time for each frame
        Uint64 deltaTime = (SDL_GetTicks() - CurrentTime) / 1000;

        GameEngine::Update(deltaTime);
        GameEngine::Render(mWindow.GetRenderer());
        
        frames++;
        // FPS Count
        if (CurrentTime > LastUpdateTime + 1000) {
            LastUpdateTime = CurrentTime;
            std::string name = "🧩 2048 - FPS: " + std::to_string(frames);
            SDL_SetWindowTitle(mWindow.GetWindow(), name.c_str());
            frames = 0;
        }

        // limiting to ~60 FPS
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
            IsKeyPressed = true;
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
    case SDLK_R:
        mGrid.Initialize(16, 2);
        std::cout << "Restart" << std::endl;
        break;
    }
}

void GameEngine::Update(float deltaTime) {
    if (IsKeyPressed) {
        mGrid.MoveTiles(Direction);
        mGrid.Update(deltaTime);
        IsKeyPressed = false;
    }
}

void GameEngine::Render(SDL_Renderer* renderer) {
    mWindow.Clear();
    mGrid.Render(renderer);
    mWindow.Present();
}