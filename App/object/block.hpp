#pragma once

#include <SFML/Graphics.hpp>

class Block : public sf::Drawable
{
    private:
        sf::RectangleShape m_shape = sf::RectangleShape(sf::Vector2f(50, 50));
    public:
        Block() {} ;
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
        Block& setPosition(sf::Vector2f position) { m_shape.setPosition(position) ; return *this; }
        Block& setColor(sf::Color color) { m_shape.setFillColor(color); return *this; }
        Block& setSize(sf::Vector2f size) { m_shape.setSize(size); return *this; }
        
        sf::Vector2f getPosition() { return m_shape.getPosition(); }
        sf::Color getColor() { return m_shape.getFillColor(); }
        sf::Vector2f getSize() { return m_shape.getSize(); }
};

class BlockCluster : public sf::Drawable
{
    private:
        std::vector<Block> m_blocks;
    public:
        
};