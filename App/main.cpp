#include <iostream>
#include <SFML/Graphics.hpp>

#include "Object/Block.hpp"
#include "System/GameSystem.hpp"
#include "System/Randomizer.hpp"

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