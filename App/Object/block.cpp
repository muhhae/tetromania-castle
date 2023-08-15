#include "Block.hpp"

void Block::draw(sf::RenderTarget & target, sf::RenderStates states) const
{   
    target.draw(m_shape);
} 

void BlockCluster::create()
{
    m_blocks.clear();
    Block block;
    
    if (m_shape == Shape::z_reverse) m_position.x += m_size;
    
    static sf::Texture g_blockTexture;
    g_blockTexture.loadFromFile("block_2.png");
    
    block.setSize(sf::Vector2f(m_size, m_size))
         .setColor(m_color)
         .setTexture(&g_blockTexture)
         .setPosition(m_position);
         
    for (int i = 0; i < 4; i++)
    {
        m_blocks.push_back(block);
    }
         
    switch (m_shape)
    {
    case Shape::line:
        for (int i = 0; i < 4; i++)
        {
            sf::Vector2f offset = sf::Vector2f(0, 0);
            offset.x += block.getSize().x * i;
            
            m_blocks[i].move(offset);
        }
        break;
    case Shape::l:
        m_blocks[1].move(sf::Vector2f(0, m_size));
        m_blocks[2].move(sf::Vector2f(0, m_size * 2));
        m_blocks[3].move(sf::Vector2f(m_size, m_size * 2));
        break;
    case Shape::l_reverse:
        m_blocks[1].move(sf::Vector2f(0, m_size));
        m_blocks[2].move(sf::Vector2f(0, m_size * 2));
        m_blocks[3].move(sf::Vector2f(-m_size, m_size * 2));
        break;
    case Shape::rectangle:
        m_blocks[1].move(sf::Vector2f(m_size, 0));
        m_blocks[2].move(sf::Vector2f(0, m_size));
        m_blocks[3].move(sf::Vector2f(m_size, m_size));
        break;
    case Shape::t:
        m_blocks[1].move(sf::Vector2f(m_size, 0));
        m_blocks[2].move(sf::Vector2f(2 * m_size, 0));
        m_blocks[3].move(sf::Vector2f(m_size, m_size));
        break;
    case Shape::z:
        m_blocks[1].move(sf::Vector2f(m_size, 0));
        m_blocks[2].move(sf::Vector2f(m_size, m_size));
        m_blocks[3].move(sf::Vector2f(m_size * 2, m_size));
        break;
    case Shape::z_reverse:
        m_blocks[1].move(sf::Vector2f(-m_size, 0));
        m_blocks[2].move(sf::Vector2f(-m_size, m_size));
        m_blocks[3].move(sf::Vector2f(-m_size * 2, m_size));
        break;
    default:
        break;
    }
    
}

void BlockCluster::move(sf::Vector2f offset)
{
    m_position += offset;
    for (auto & block : m_blocks)
        block.move(offset);
}


void BlockCluster::rotate()
{
    if (Shape::rectangle == m_shape) return;
    
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

sf::Vector2f BlockCluster::getBottomPosition()
{
    sf::Vector2f bottom = m_blocks[0].getPosition();
    for (auto& block : m_blocks)
    {
        if (block.getPosition().y > bottom.y)
            bottom = block.getPosition();
    }
    return bottom + sf::Vector2f(0, getSize());
}
