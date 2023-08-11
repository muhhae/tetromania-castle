#include "block.hpp"

void Block::draw(sf::RenderTarget & target, sf::RenderStates states) const
{   
    target.draw(m_shape);
} 