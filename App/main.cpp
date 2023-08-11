#include <iostream>
#include <SFML/Graphics.hpp>

#include "object/block.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 800), "SFML works!");
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(window.getSize()));
    window.setView(view);
    
    Block block;
    
    block.setColor(sf::Color::Red)
         .setPosition(sf::Vector2f(100, 100))
         .setSize(sf::Vector2f(50, 50));
    
    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                view.setSize(event.size.width, event.size.height);
                window.setView(view);
            }
        }
        
        window.clear(sf::Color::Black);
        window.draw(block);
        window.display();
    }

    return 0;
}