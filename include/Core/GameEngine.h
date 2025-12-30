#pragma once
#include "Grid.h"
#include "Graphics/Window.h"

class GameEngine {
    Window mWindow;
    Grid mGrid;
    Key Direction;
    bool mRunning;
public:
    GameEngine(const std::string& title, float width, float height);
    ~GameEngine();
    bool Initialize();
    void Run();
    void ShutDown();
private:
    void HandleEvents();
    void HandleInputs(SDL_Keycode key);
    void Update();
    void Render(SDL_Renderer* renderer);
};