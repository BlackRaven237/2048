#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Grid.h"
#include "Graphics\Window.h"
#include <SDL3/SDL_timer.h>

class GameEngine {
    Window mWindow;
    Grid mGrid;
    Key Direction;
    bool IsKeyPressed;
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

#endif