#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Grid.h"
#include "Graphics\Window.h"
#include <iostream>
#include <SDL3/SDL_timer.h>

class GameEngine {
    Window* mWindow;
    Grid mGrid;
    Key Direction;
    bool IsKeyPressed;
    bool isInitialized;
    bool mRunning;
    std::string m_fpsCount;
public:
    GameEngine(const std::string& title, float width, float height);
    ~GameEngine();
    bool Initialize();
    void Run();
    void ShutDown();
private:
    void HandleEvents();
    void HandleInputs(SDL_Keycode key);
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
};

#endif