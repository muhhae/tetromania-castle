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

inline static std::vector<BlockCluster> blockClusters;

BlockCluster & instantiate(BlockCluster::Shape shape = BlockCluster::Shape::rectangle, 
                           sf::Vector2f position = sf::Vector2f(0, 0),
                           sf::Color color = sf::Color::Red, 
                           float size = 50)
{
    blockClusters.push_back(BlockCluster());
    blockClusters.back().setPosition(position)
                        .setColor(color)
                        .setSize(size)
                        .setShape(shape);
    blockClusters.back().create();
    
    return blockClusters.back();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 800), "SFML works!");
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(window.getSize()));
    window.setView(view);
    
    sf::Clock clock;
    sf::Time dt;
    
    int shape = 0;
    
    BlockCluster & blockCluster = instantiate(BlockCluster::Shape::rectangle, 
                                              sf::Vector2f(0, 0),
                                              sf::Color::Red, 
                                              50);
    
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
                    blockCluster.setColor(sf::Color::Blue)
                                .setShape(static_cast<BlockCluster::Shape>(shape));
                    blockCluster.create();
                    shape++;
                    if (shape == static_cast<int>(BlockCluster::Shape::MAX))
                        shape = 0;
                }
            }
        }
        
        static float elapsedTime = 0;
        elapsedTime += dt.asSeconds();
        
        if (elapsedTime >= 1 )
        {
            elapsedTime = 0;
            blockCluster.move(sf::Vector2f(0, blockCluster.getSize()));
        }
        
        window.clear(sf::Color::Black);
        window.draw(blockCluster);  
        window.display();
    }

    return 0;
}