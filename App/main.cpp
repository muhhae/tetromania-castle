#include <iostream>
#include <SFML/Graphics.hpp>

#include "object/block.hpp"

void input(Block & block, sf::Time dt)
{
    sf::Vector2f move;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        move.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        move.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        move.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        move.y += 1;
        
    block.move(move * dt.asSeconds());
}

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
            move.y -= offset;
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
    
    Block block;
    
    block.setColor(sf::Color::Red)
         .setPosition(sf::Vector2f(100, 100))
         .setSize(sf::Vector2f(50, 50));
         
    BlockCluster blockCluster;
    blockCluster.create(BlockCluster::Shape::z_reverse,sf::Vector2f(-200, -200));
    
    sf::Clock clock;
    sf::Time dt;
    
    while (window.isOpen())
    {
        dt = clock.restart();
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            input(block, event);
            input(blockCluster, event);
            
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                view.setSize(event.size.width, event.size.height);
                window.setView(view);
            }
        }
        
        // input(block, dt);
        
        window.clear(sf::Color::Black);
        // window.draw(block);
        window.draw(blockCluster);  
        window.display();
    }

    return 0;
}