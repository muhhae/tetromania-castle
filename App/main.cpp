#include <iostream>
#include <SFML/Graphics.hpp>

#include "object/block.hpp"

void input(Block & block, sf::Event event)
{
    sf::Vector2f move;
    float offset = block.getSize().x;
    
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Left)
            move.x -= offset;
        if (event.key.code == sf::Keyboard::Right)
            move.x += offset;
        if (event.key.code == sf::Keyboard::Up)
            move.y -= offset;
        if (event.key.code == sf::Keyboard::Down)
            move.y += offset;
    }
        
    block.move(move);
}

void input(BlockCluster& blockCluster, sf::Event event)
{
    sf::Vector2f move;
    float offset = blockCluster.getSize();
    
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Left)
            move.x -= offset;
        if (event.key.code == sf::Keyboard::Right)
            move.x += offset;
        if (event.key.code == sf::Keyboard::Up)
            blockCluster.rotate();
        if (event.key.code == sf::Keyboard::Down)
            move.y += offset;
    }
    
    blockCluster.move(move);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 800), "SFML works!");
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(window.getSize()));
    window.setView(view);
    
    BlockCluster blockCluster;
    blockCluster.create(BlockCluster::Shape::z_reverse,
                        sf::Vector2f(-200, -200), 
                        sf::Color::Green, 50);
    
    sf::Clock clock;
    sf::Time dt;
    
    int shape = 0;
    
    while (window.isOpen())
    {
        dt = clock.restart();
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            input(blockCluster, event);
            
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
                    blockCluster.create(static_cast<BlockCluster::Shape>(shape),
                                        sf::Vector2f(-200, -200), 
                                        sf::Color::Green, 50);
                    shape++;
                    if (shape == static_cast<int>(BlockCluster::Shape::MAX))
                        shape = 0;
                }
            }
        }
        
        window.clear(sf::Color::Black);
        window.draw(blockCluster);  
        window.display();
    }

    return 0;
}