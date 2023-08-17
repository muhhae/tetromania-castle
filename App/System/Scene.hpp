#pragma once

#include "GameSystem.hpp"

class Scene
{
    public:
        virtual void run(sf::RenderWindow & window) = 0;
        virtual void init(sf::RenderWindow & window) = 0;
};


