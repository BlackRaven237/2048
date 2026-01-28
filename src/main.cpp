#include "../include/Core/GameEngine.h"
#include <ctime>

int main (int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    srand(static_cast<unsigned int>(time(nullptr)));

    std::cout << " ====== Welcome to my 2048 puzzle Game ====== " << std::endl;
    GameEngine* Game = new GameEngine("🧩2048", 500.0f, 600.0f);
    if(!Game->Initialize()) {
        std::cerr << "❌ Couldn't launch game" << std::endl;
    }

    Game->Run();

    if (Game) {
        delete Game;
        Game = nullptr;
    }

    std::cout << "👋 Thanks for playing" << std::endl;
    return 0;
}