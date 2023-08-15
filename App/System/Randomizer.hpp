#pragma once

#include "GameSystem.hpp"

BlockCluster::Shape randomShape()
{
    return BlockCluster::Shape::t;
    return static_cast<BlockCluster::Shape>(rand() % static_cast<int>(BlockCluster::Shape::MAX));
}

sf::Color randomColor()
{
    std::array<sf::Color, 4> colors = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow};
    
    return colors[rand() % colors.size()];
}

sf::Vector2f randomPosition()
{
    int tile = (g_screen.width - 300) / 50;
    return sf::Vector2f((rand() % tile) * 50 - g_screen.right + 150, g_screen.top);
}