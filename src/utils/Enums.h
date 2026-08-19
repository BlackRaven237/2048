#pragma once

enum class Key {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

enum class GameState {
    StartMenu,
    Playing,
    GameOver,
    Won
};