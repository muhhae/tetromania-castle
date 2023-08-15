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

inline int g_score = 0;

void initGameScreen(int width, int height)
{
    g_screen.width = width;
    g_screen.height = height;
    g_screen.top = -height / 2;
    g_screen.bottom = height / 2;
    g_screen.left = -width / 2;
    g_screen.right = width / 2;
}

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
        if (block.getPosition().x + offset.x < g_screen.left ||
            block.getPosition().x + offset.x >= g_screen.right ||
            block.getPosition().y + offset.y >= g_screen.bottom)
        {
            std::cout << "\nPos : " << block.getPosition().x + offset.x << ", " << block.getPosition().y + offset.y << std::endl;
            std::cout << "Out of bound" <<std::endl;
            return false;
        }
    }
    
    for (auto& bc : blockClusters)
    {
        if (&blockCluster == &bc) continue;
        
        for (auto& block : blockCluster.getBlocks())
        {
            for (auto& b : bc.getBlocks())
            {   
                if (block.getPosition() + offset == b.getPosition())
                {
                    std::cout << "\nPos : " << block.getPosition().x + offset.x << ", " << block.getPosition().y + offset.y << std::endl;
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
            block.getPosition().x >= g_screen.right ||
            block.getPosition().y >= g_screen.bottom)
        {
            // std::cout << "Out of bound" <<std::endl;
            // std::cout << "failRotate" <<std::endl;
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
                    std::cout << "Pos : " << block.getPosition().x << ", " << block.getPosition().y << std::endl;
                    std::cout << "Collide\n" <<std::endl;
                    return false;
                }
            }
        }
    }
    blockCluster.rotate();
}

bool moveBlock(Block & block, sf::Vector2f offset)
{
    if (block.getPosition().x + offset.x < g_screen.left ||
        block.getPosition().x + offset.x >= g_screen.right ||
        block.getPosition().y + offset.y >= g_screen.bottom)
    {
        std::cout << "\nPos : " << block.getPosition().x + offset.x << ", " << block.getPosition().y + offset.y << std::endl;
        std::cout << "Out of bound" <<std::endl;
        return false;
    }
    
    for (auto & blockCluster : blockClusters)
    {
        for (auto & b : blockCluster.getBlocks())
        {
            if (block.getPosition() + offset == b.getPosition())
            {
                std::cout << "\nPos : " << block.getPosition().x + offset.x << ", " << block.getPosition().y + offset.y << std::endl;
                std::cout << "Collide" <<std::endl;
                return false;
            }
        }
    }
    
    block.move(offset);
    return true;
}

void betterCheckLine()
{
    const int maxLine = 12;
    
    struct lineInfo
    {
        lineInfo(float y, int count) : y(y), count(count) {}
        float y;
        int count = 0;
    };
    
    std::vector<lineInfo> lines;
    
    for (auto& bc : blockClusters)
    {
        auto& blocks = bc.getBlocks();
        for (auto& block : blocks)
        {
            auto iter = std::find_if(lines.begin(), lines.end(), [&](lineInfo& line){return line.y == block.getPosition().y;});
            if (iter != lines.end())
            {
                iter->count++;
            }
            else
            {
                lines.push_back(lineInfo(block.getPosition().y, 1));
            }
            
        }
    }
    
    int lineCount = 0;
    
    for (auto& line : lines)
    {
        if (line.count >= maxLine)
        {
            lineCount++;
            g_score += 1000;
            for (auto & blockCluster : blockClusters)
            {
                auto & blocks = blockCluster.getBlocks();
                
                deleteAll<Block>(blocks, [&](Block& block){return block.getPosition().y == line.y;});
            }  
        }
    }
    
    if (lineCount <= 0) return;
    
    deleteAll<BlockCluster>(blockClusters, [&](BlockCluster& blockCluster){return blockCluster.getBlocks().empty();});
    
    for (int i = 0; i < lineCount; i++)
    {
        std::cout << "\nMoving down\n";
        for (auto& blockCluster : blockClusters)
        {
            for (auto& block : blockCluster.getBlocks())
            {
                if (!moveBlock(block, sf::Vector2f(0, block.getSize().y)))
                {
                    std::cout << "fail\n";
                }
            }
        }
    }
}

bool checkLose()
{
    for (auto& blockCluster : blockClusters)
    {
        if (&blockCluster == &blockClusters.back()) break;
        for (auto& block : blockCluster.getBlocks())
        {
            if (block.getPosition().y <= g_screen.top)
            {
                std::cout << "Lose" << std::endl;
                return true;
            }
        }
    }
    return false;
}
