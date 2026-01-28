#include "Core\GameEngine.h"

GameEngine::GameEngine(const std::string& title, float width, float height) : 
    mWindow(new Window(title, width, height)),
    mGrid(Vector2D(0.0f, height - width), width), 
    Direction(Key::NONE), IsKeyPressed(false), 
    isInitialized(false), mRunning(false) {}

GameEngine::~GameEngine() {
    ui.Shutdown();

    if (mWindow) {
        delete mWindow;
        mWindow = nullptr;
    }

    GameEngine::ShutDown();
}

bool GameEngine::Initialize() {
    if(!mWindow->Initialize()) isInitialized = false;

    mGrid.Initialize(2);

    ui.Init(mWindow->GetWindow(), mWindow->GetRenderer()->GetRenderer());

    isInitialized = true;
    mRunning = true;
    std::cout << "🚀 GameEngine is correctly initialized" << std::endl;
    return isInitialized;
}

void GameEngine::ShutDown() {
    std::cout << "🛑 GameEngine correctly stops" << std::endl;
}

void GameEngine::Run() {
    Uint64 LastUpdateTime = SDL_GetTicks();
    Uint64 fpsTimer = SDL_GetTicks();
    int frames = 0;

    while(mRunning) {
        GameEngine::HandleEvents();

        // elasped time for each frame
        Uint64 CurrentTime = SDL_GetTicks();
        float deltaTime = (CurrentTime - LastUpdateTime) / 1000.0f;
        LastUpdateTime = CurrentTime;

        GameEngine::Update(deltaTime);

        ui.BeginFrame();
        if(ui.RenderGameUI(mGrid.GetScore(), 100000)) {
            mGrid.Reset();
            mGrid.Initialize(2);
            std::cout << "🔁 Restart" << std::endl;
        }

        // FPS calculation
        frames++;
        if (SDL_GetTicks() > fpsTimer + 1000) {
            std::string newTitle = "🧩 2048 - FPS: " + std::to_string(frames);
            SDL_SetWindowTitle(mWindow->GetWindow(), newTitle.c_str());
            m_fpsCount = std::to_string(frames) + " FPS";
            frames = 0;
            fpsTimer = SDL_GetTicks();
        }

        GameEngine::Render(mWindow->GetRenderer());
        // limiting to ~60 FPS
        // Achieved by the use of SDL_RenderVSync() in Renderer class
    }
}

void GameEngine::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ui.HandleEvent(&event);
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
        IsKeyPressed = true;
        break;
    case SDLK_DOWN:
        Direction = Key::DOWN;
        IsKeyPressed = true;
        break;
    case SDLK_LEFT:
        Direction = Key::LEFT;
        IsKeyPressed = true;
        break;
    case SDLK_RIGHT:
        Direction = Key::RIGHT;
        IsKeyPressed = true;
        break;
    case SDLK_R:
        mGrid.Reset();
        mGrid.Initialize(2);
        std::cout << "🔁 Restart" << std::endl;
        break;
    case SDLK_ESCAPE:
        mRunning = false;
        break;
    default: 
        break;
    }
}

void GameEngine::Update(float deltaTime) {
    if (IsKeyPressed) {
        mGrid.MoveTiles(Direction);
        IsKeyPressed = false;
    }

    mGrid.Update(deltaTime);
}

bool GameEngine::CheckWin() {
    return mGrid.CheckWin();
}

bool GameEngine::IsGameOver() {
    return mGrid.IsGameOver();
}

void GameEngine::Render(Renderer* renderer) {
    mWindow->Clear();
    mGrid.Render(renderer);
    ui.Render(renderer->GetRenderer());
    mWindow->Present();
}