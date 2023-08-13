#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "object/block.hpp"

struct gameScreen 
{
    int width;
    int height;
    int top, bottom, left, right;
};
inline gameScreen g_screen;

inline std::vector<BlockCluster> blockClusters;
inline bool moveBlockCluster(BlockCluster& blockCluster, sf::Vector2f offset);
inline bool rotateBlockCluster(BlockCluster& blockCluster);

void instantiate(BlockCluster::Shape shape = BlockCluster::Shape::rectangle, 
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
}

bool input(BlockCluster& blockCluster, sf::Event event)
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
            rotateBlockCluster(blockCluster);
        if (event.key.code == sf::Keyboard::Down)
            move.y += offset;
    }
    return moveBlockCluster(blockCluster, move);
}

bool moveBlockCluster(BlockCluster& blockCluster, sf::Vector2f offset)
{
    for (auto& block : blockCluster.getBlocks())
    {
        if (!block.getActive()) continue;
        if (block.getPosition().x + offset.x < g_screen.left ||
            block.getPosition().x + offset.x > g_screen.right ||
            block.getPosition().y + offset.y >= g_screen.bottom)
        {
            std::cout << "Pos : " << block.getPosition().x + offset.x << ", " << block.getPosition().y + offset.y << std::endl;
            std::cout << "Out of bound" <<std::endl;
            return false;
        }
    }
    
    for (auto& bc : blockClusters)
    {
        if (&blockCluster == &bc) continue;
        
        for (auto& block : blockCluster.getBlocks())
        {
            if (!block.getActive()) continue;
            for (auto& b : bc.getBlocks())
            {   
                if (!b.getActive()) continue;
                if (block.getPosition() + offset == b.getPosition())
                {
                    std::cout << "Collide" <<std::endl;
                    return false;
                }
            }
        }
    }
    blockCluster.move(offset);
    return true;
}

bool rotateBlockCluster(BlockCluster& blockCluster)
{
    BlockCluster temp = blockCluster;
    temp.rotate();
    
    for (auto& block : temp.getBlocks())
    {
        if (!block.getActive()) continue;
        
        if (block.getPosition().x < g_screen.left ||
            block.getPosition().x > g_screen.right ||
            block.getPosition().y >= g_screen.bottom)
        {
            std::cout << "Out of bound" <<std::endl;
            std::cout << "failRotate" <<std::endl;
            return false;
        }
    }
    
    for (auto& bc : blockClusters)
    {
        if (&blockCluster == &bc) continue;
        
        for (auto& block : temp.getBlocks())
        {
            if (!block.getActive()) continue;
            
            for (auto& b : bc.getBlocks())
            {   
                if (!b.getActive()) continue;
                if (block.getPosition() == b.getPosition())
                {
                    std::cout << "Collide" <<std::endl;
                    return false;
                }
            }
        }
    }
    blockCluster.rotate();
}

BlockCluster::Shape randomShape()
{
    // return BlockCluster::Shape::rectangle;
    return static_cast<BlockCluster::Shape>(rand() % static_cast<int>(BlockCluster::Shape::MAX));
}

sf::Color randomColor()
{
    return sf::Color(rand() % 255, rand() % 255, rand() % 255);
}

sf::Vector2f randomPosition()
{
    int tile = (g_screen.width - 300) / 50;
    return sf::Vector2f((rand() % tile) * 50 - g_screen.right, g_screen.top);
}

void checkLine()
{
    const int maxLine = 13;
    struct blockInfo
    {
        int blockClusterIndex;
        int blockIndex;
    };
    
    std::map<int, std::vector<blockInfo>> lines;
    
    for (int i = 0; i < blockClusters.size(); i++)
    {
        auto & blocks = blockClusters[i].getBlocks();
        for (int j = 0; j < blocks.size(); j++)
        {
            auto & block = blocks[j];
            lines[block.getPosition().y].push_back({i, j});
        }
    }
    
    for (auto & line : lines)
    {
        if (line.second.size() >= maxLine)
        {
            for (auto & blockInfo : line.second)
            {
                blockClusters[blockInfo.blockClusterIndex].getBlocks().at(blockInfo.blockIndex) = Block();
                blockClusters[blockInfo.blockClusterIndex].getBlocks().at(blockInfo.blockIndex)
                                                                      .setActive(false);
            }
        }
    }
    for (auto& blockCluster : blockClusters)
        moveBlockCluster(blockCluster, sf::Vector2f(0, blockCluster.getSize()));
}