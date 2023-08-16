#include "Randomizer.hpp"

#include <array>

BlockCluster::Shape randomShape()
{
    // return BlockCluster::Shape::t;
    return static_cast<BlockCluster::Shape>(rand() % static_cast<int>(BlockCluster::Shape::MAX));
}

sf::Color randomColor()
{
    std::array<sf::Color, 4> colors = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow};
    sf::Color color = colors[rand() % colors.size()];
    color.r /= 2;
    color.g /= 2;
    color.b /= 2;
    return color;
}

sf::Vector2f randomPosition()
{
    int tile = (g_screen.width - 300) / 50;
    return sf::Vector2f((rand() % tile) * 50 - g_screen.right + 150, g_screen.top);
}