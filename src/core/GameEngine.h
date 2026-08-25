#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "../entities/Grid.h"
#include "../graphics/Window.h"
#include "../graphics/Renderer.h"
#include "../graphics/RendererUI.h"
#include <iostream>
#include <SDL3/SDL_timer.h>

class GameEngine {
    Window* mWindow;
    UI ui;
    Grid mGrid;
    Key Direction = Key::NONE;

    bool IsKeyPressed = false;
    bool isInitialized = false;
    bool mRunning = false;

    std::string m_fpsCount;
public:
    GameEngine(const std::string& title, float width, float height);
    ~GameEngine();
    bool Initialize();
    void Run();
private:
    void ResetGame();
    void HandleEvents();
    void HandleInputs(SDL_Keycode key);
    void Update(float deltaTime);
    void Render(Renderer* renderer);

    float calculateDeltaTime(Uint64& lastUpdateTime, Uint64& currentTime);
    void calculateFPS(Uint64& fpsTimer, int& frames);
};

#endif