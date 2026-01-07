#include "include/Core/GameEngine.h"
#include <cstdlib>
#include <ctime>

int main (int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(nullptr)));

    std::cout << " ====== Welcome to my 2048 puzzle Game ====== " << std::endl;
    GameEngine game("🧩2048", 800, 640);
    if(!game.Initialize()) {
        std::cerr << "Game Engine couldn't launch" << std::endl;
    }
    game.Run();
    return 0;
}