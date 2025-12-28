#pragma once
#include "Grid.h"

class GameEngine {
    Grid mGrid;
    bool mRunning;
public:
    GameEngine();
    ~GameEngine();
    bool Initialize();
    void Run();
    void ShutDown();
private:
    void HandleEvents();
    void HandleInputs();
    void Update();
    void Render();
};