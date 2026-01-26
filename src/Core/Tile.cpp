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
    float speed = 20.0f;
    position.x += (targetPosition.x - position.x) * speed * deltaTime;
    position.y += (targetPosition.y - position.y) * speed * deltaTime;

    if (std::abs(targetPosition.x - position.x) < 0.1f) position.x = targetPosition.x;
    if (std::abs(targetPosition.y - position.y) < 0.1f) position.y = targetPosition.y;

    // Spawning pop-up effects
    if (scale < 1.0f) {
        scale += 5.0f * deltaTime;
        if (scale > 1.0f) scale = 1.0f;
    }
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

Color Tile::GetColorBasedOnValue() const {
    switch (m_value) {
        case 2: return Color(238, 228, 218);
        case 4: return Color(237, 224, 200);
        case 8: return Color(242, 177, 121);
        case 16: return Color(245, 149, 99);
        case 32: return Color(246, 124, 95);
        case 64: return Color(246, 94, 59);
        case 128: return Color(237, 207, 114);
        case 256: return Color(237, 204, 97);
        case 512: return Color(237, 200, 80);
        case 1024: return Color(237, 197, 63);
        case 2048: return Color(237, 194, 46);
        default: return Color(199, 110, 101);
    }
}

void Tile::Render(Window* window)
{
    float drawSize = size * scale;
    float offset = (size - drawSize) / 2;

    SDL_FRect tile = {
        position.x + offset,
        position.y + offset,
        drawSize,
        drawSize
    };

    color = GetColorBasedOnValue();

    SDL_SetRenderDrawColor(window->GetRenderer(), color.red, color.green, color.blue, 255);
    SDL_RenderFillRect(window->GetRenderer(), &tile);

    RenderValue(window);
}