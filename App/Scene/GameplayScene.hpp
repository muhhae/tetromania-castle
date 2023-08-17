#pragma once
#include "System/Scene.hpp"
#include <SFML/Audio.hpp>

class GameplayScene : public Scene
{
    public:
        virtual void run(sf::RenderWindow & window);
        virtual void init(sf::RenderWindow & window);
    private:
        void restart();
        void instantiate(BlockCluster::Shape shape = BlockCluster::Shape::rectangle, 
                     sf::Vector2f position = sf::Vector2f(0, 0),
                     sf::Color color = sf::Color::Red, 
                     float size = 50);
        bool betterCheckLine();
        bool input(BlockCluster& blockCluster, sf::Event event);
        bool moveBlockCluster(BlockCluster& blockCluster, sf::Vector2f offset);
        bool rotateBlockCluster(BlockCluster& blockCluster);
        bool moveBlock(Block & block, sf::Vector2f offset);
        bool checkLose();
    private:
        std::vector<BlockCluster> blockClusters;
        int g_score = 0;
        bool lose = false;
        
        sf::View view;
};