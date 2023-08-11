#include "block.hpp"

void Block::draw(sf::RenderTarget & target, sf::RenderStates states) const
{   
    target.draw(m_shape);
} 

void BlockCluster::create(Shape shape, sf::Vector2f position, float size)
{
    m_blocks.clear();
            
    Block block;
    block.setPosition(position)
         .setColor(sf::Color::Red)
         .setSize(sf::Vector2f(size, size));
         
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
        for (int i = 0; i < 4; i++)
        {
            sf::Vector2f offset = sf::Vector2f(0, 0);
            offset.y += size * i;
            
            m_blocks[i].move(offset);
        }
        m_blocks[3].move(sf::Vector2f(size, -size));
        break;
    case Shape::l_reverse:
        for (int i = 0; i < 4; i++)
        {   
            sf::Vector2f offset = sf::Vector2f(0, 0);
            offset.y += size * i;
            
            m_blocks[i].move(offset);
        }
        m_blocks[3].move(sf::Vector2f(-size, -size));
        break;
    case Shape::rectangle:
        m_blocks[1].move(sf::Vector2f(size, 0));
        m_blocks[2].move(sf::Vector2f(0, size));
        m_blocks[3].move(sf::Vector2f(size, size));
        break;
    case Shape::t:
        m_blocks[1].move(sf::Vector2f(size, 0));
        m_blocks[2].move(sf::Vector2f(-size, 0));
        m_blocks[3].move(sf::Vector2f(0, size));
        break;
    case Shape::z:
        m_blocks[1].move(sf::Vector2f(size, 0));
        m_blocks[2].move(sf::Vector2f(size, size));
        m_blocks[3].move(sf::Vector2f(size * 2, size));
    case Shape::z_reverse:
        m_blocks[1].move(sf::Vector2f(size, 0));
        m_blocks[2].move(sf::Vector2f(0, size));
        m_blocks[3].move(sf::Vector2f(-size, size));
        break;
    default:
        break;
    }
    
}

void BlockCluster::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    for (auto & block : m_blocks)
        target.draw(block);
}