#include "block.hpp"

void Block::draw(sf::RenderTarget & target, sf::RenderStates states) const
{   
    target.draw(m_shape);
} 

void BlockCluster::create(Shape shape, sf::Vector2f position, sf::Color color, float size)
{
    m_blocks.clear();
    
    Block block;
    
    if (shape == Shape::z_reverse) position.x += size;
    
    block.setSize(sf::Vector2f(size, size))
         .setColor(color)
         .setPosition(position);
         
    for (int i = 0; i < 4; i++)
    {
        m_blocks.push_back(block);
    }
         
    switch (shape)
    {
    case Shape::line:
        for (int i = 0; i < 4; i++)
        {
            m_blocks.push_back(block);
            
            sf::Vector2f offset = sf::Vector2f(0, 0);
            offset.x += block.getSize().x * i;
            
            m_blocks[i].move(offset);
        }
        break;
    case Shape::l:
        m_blocks[1].move(sf::Vector2f(0, size));
        m_blocks[2].move(sf::Vector2f(0, size * 2));
        m_blocks[3].move(sf::Vector2f(size, size * 2));
        break;
    case Shape::l_reverse:
        m_blocks[1].move(sf::Vector2f(0, size));
        m_blocks[2].move(sf::Vector2f(0, size * 2));
        m_blocks[3].move(sf::Vector2f(-size, size * 2));
        break;
    case Shape::rectangle:
        m_blocks[1].move(sf::Vector2f(size, 0));
        m_blocks[2].move(sf::Vector2f(0, size));
        m_blocks[3].move(sf::Vector2f(size, size));
        break;
    case Shape::t:
        m_blocks[1].move(sf::Vector2f(size, 0));
        m_blocks[2].move(sf::Vector2f(2 * size, 0));
        m_blocks[3].move(sf::Vector2f(size, size));
        break;
    case Shape::z:
        m_blocks[1].move(sf::Vector2f(size, 0));
        m_blocks[2].move(sf::Vector2f(size, size));
        m_blocks[3].move(sf::Vector2f(size * 2, size));
        break;
    case Shape::z_reverse:
        m_blocks[1].move(sf::Vector2f(-size, 0));
        m_blocks[2].move(sf::Vector2f(-size, size));
        m_blocks[3].move(sf::Vector2f(-size * 2, size));
        break;
    default:
        break;
    }
    
}

void BlockCluster::rotate()
{
    sf::Vector2f center = m_blocks[1].getPosition();
    
    for (auto & block : m_blocks)
    {
        sf::Vector2f offset = block.getPosition() - center;
        
        block.setPosition(center + sf::Vector2f(offset.y, -offset.x));
    }
}

void BlockCluster::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    for (auto & block : m_blocks)
        target.draw(block);
}