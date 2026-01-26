#include "Core/Tile.h"

Tile::Tile(int value, Vector2D pos, int row, int column, float size) : 
    m_value(value), position(pos), 
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

void Tile::RenderValue(Window* window) {
    std::string value = std::to_string(m_value);
    //std::pair<float, float> text = window->textSize;

    float x = position.x; //+ ((size - text.first) / 4);
    float y = position.y; //+ ((size - text.second) / 4);

    window->RenderText(value, x, y, GetTextColor());
}

Color Tile::GetTextColor() const {
    // Dark grey text for '2' and '4' values
    if(m_value <= 4) return Color(119, 110, 101);
    
    // off-white for remaining values
    return Color(249, 246, 242);
}

void Tile::Render(Window* window)
{
    SDL_FRect tile = {
        position.x,
        position.y,
        size,
        size
    };

    SDL_SetRenderDrawColor(window->GetRenderer(), color.red, color.green, color.blue, 255);
    SDL_RenderFillRect(window->GetRenderer(), &tile);

    RenderValue(window);
}