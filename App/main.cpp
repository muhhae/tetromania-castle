#include "System/GameSystem.hpp"

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}