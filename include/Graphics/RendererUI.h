#ifndef RENDERER_UI_H
#define RENDERER_UI_H

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

class UI {
public:
    UI();
    ~UI();

    // Initialize ImGui and SDL3 backends
    void Init(SDL_Window* window, SDL_Renderer* renderer);

    // Pass SDL events to ImGui (clicks, keys, resizing)
    void HandleEvent(const SDL_Event* event);

    // Start a new frame (call this before drawing any UI)
    void BeginFrame();

    // Render the actual UI elements (Score, Menu, etc.)
    // Returns true if "Reset" was clicked
    bool RenderGameUI(int currentScore, int bestScore);

    // Finalize the frame and send draw data to SDL
    void Draw(SDL_Renderer* renderer);

    // Clean up memory
    void Shutdown();

private:
    void ApplyCustomTheme();
};
#endif
