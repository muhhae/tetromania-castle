#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <deque>
#include <array>
#include <iostream>
#include <unordered_map>
#include <functional>

#include "Object/Block.hpp"
#include "GeneralFunction.hpp"
#include "Randomizer.hpp"
#include "Global.hpp"


class Game
{
public : //public function
    // @brief Running the Game
    // @param none
    // @return none
    void run();
    void init(sf::RenderWindow & window);
    void restart();
private : //private function
    // @brief Instantiate a block cluster
    // @param shape of the block cluster
    // @param position of the block cluster
    // @param color of the block cluster
    // @param size of the blocks
    // @return none
    void instantiate(BlockCluster::Shape shape = BlockCluster::Shape::rectangle, 
                     sf::Vector2f position = sf::Vector2f(0, 0),
                     sf::Color color = sf::Color::Red, 
                     float size = 50);
    // @brief Check if the line is full
    // @param none
    // @return none
    void betterCheckLine();
    // @brief Take input from player
    // @param BlockCluster
    // @param sf::Event
    // @return True from @ref moveBlockCluster() or @ref rotateBlockCluster()
    bool input(BlockCluster& blockCluster, sf::Event event);
    // @brief Move the block cluster
    // @param BlockCluster
    // @param offset
    // @return True if the block cluster can move
    bool moveBlockCluster(BlockCluster& blockCluster, sf::Vector2f offset);
    // @brief Rotate the block cluster
    // @param BlockCluster
    // @return True if the block can rotate
    bool rotateBlockCluster(BlockCluster& blockCluster);
    // @brief Move the block
    // @param Block
    // @param offset
    // @return True if the block can move
    bool moveBlock(Block & block, sf::Vector2f offset);
    // @brief Check if Lose
    // @param BlockCluster
    // @return True if the the highest BlockCluster is on the Top of the screen
    bool checkLose();
private : //private struct

private : //private variable
    std::vector<BlockCluster> blockClusters;
    int g_score = 0;
    bool lose = false;
    
    sf::View view;
        
};


