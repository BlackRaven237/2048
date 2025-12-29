#include "include/Core/GameEngine.h"

int main (int argc, char* argv[]) {
    std::cout << " ====== Welcome to my 2048 puzzle Game ====== " << std::endl;
    GameEngine game("🧩2048", 800, 640);
    if(!game.Initialize()) {
        std::cerr << "Game Engine couldn't launch" << std::endl;
    }
    game.Run();
    game.ShutDown();
    return 0;
}