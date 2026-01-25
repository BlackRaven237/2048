#include "Core/Tile.h"

Tile::Tile(Vector2D pos, int row, int column, float size) : 
    m_value(2), position(pos), 
    row(row), column(column), 
    size(size), color(Color::Green()) {}

Tile::Tile(const Tile &other) : 
    m_value(other.m_value), position(other.position), 
    row(other.row), column(other.column),
    size(other.size), color(other.color) {}

void Tile::Move(Vector2D targetPosition, float deltaTime) {    
    float speed = 30.0f;
    position.x += (targetPosition.x - position.x) * speed * deltaTime;
    position.y += (targetPosition.y - position.y) * speed * deltaTime;

    if (std::abs(targetPosition.x - position.x) < 0.01f) position.x = targetPosition.x;
    if (std::abs(targetPosition.y - position.y) < 0.01f) position.y = targetPosition.y;
}

// void Tile::Initialize() {
//     font.InitializeFont("assets/fonts/Roboto-Bold.ttf");
//     font.SetFontColor(Color::Black());
// }

// void Tile::RenderValue(Window& window, SDL_Renderer *renderer) {
//     std::string value = std::to_string(m_value);

//     //float surfaceSize = static_cast<float>(surface->w) / 8;
//     //float x = (size - surfaceSize) / 2;
//     window.RenderText(value, position.x, position.y, Color::White());
// }

void Tile::Render(SDL_Renderer *renderer)
{
    SDL_FRect tile = {
        position.x,
        position.y,
        size,
        size
    };

    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 255);
    SDL_RenderFillRect(renderer, &tile);
}