#include <iostream>
#include <SFML/Graphics.hpp>

#include "object/block.hpp"
#include "gameplay/GameSystem.hpp"

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(600, 800), "SFML works!");
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(window.getSize()));
    window.setView(view);
    
    g_screen.bottom = view.getSize().y / 2;
    g_screen.top = view.getSize().y / -2;
    g_screen.left = view.getSize().x / -2;
    g_screen.right = view.getSize().x / 2;
    
    g_screen.width = view.getSize().x;
    g_screen.height = view.getSize().y;
        
    sf::Clock clock;
    sf::Time dt;
    
    int shape = 0;
    
    instantiate(randomShape(), 
                randomPosition(), 
                randomColor(), 
                50);
    
    while (window.isOpen())
    {
        dt = clock.restart();
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            input(blockClusters.back(), event);
            
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                view.setSize(event.size.width, event.size.height);
                window.setView(view);
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    instantiate(randomShape(), 
                                randomPosition(), 
                                sf::Color::Red, 
                                50);
                }
            }
        }
        
        static float elapsedTime = 0;
        elapsedTime += dt.asSeconds();
        
        if (elapsedTime >= 1)
        {
            elapsedTime = 0;
            if (!moveBlockCluster(blockClusters.back(), sf::Vector2f(0, blockClusters.back().getSize())))
            {
                checkLine();
                instantiate(randomShape(), 
                            randomPosition(), 
                            randomColor(), 
                            50);
            }
        }
        
        window.clear(sf::Color::Black);
            for (const auto& blockCluster : blockClusters)
                window.draw(blockCluster);
        window.display();
    }

    return 0;
}