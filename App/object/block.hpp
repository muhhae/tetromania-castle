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
        
        void move(sf::Vector2f offset) { m_shape.move(offset); }
        
        sf::Vector2f getPosition() { return m_shape.getPosition(); }
        sf::Color getColor() { return m_shape.getFillColor(); }
        sf::Vector2f getSize() { return m_shape.getSize(); }
};

class BlockCluster : public sf::Drawable
{
    private:
        std::vector<Block> m_blocks;
    public:
        enum class Shape
        {
            rectangle, line, l, l_reverse, t, z, z_reverse, 
            MAX
        };
        
    public:
        void create(Shape shape = Shape::rectangle, 
                    sf::Vector2f position = sf::Vector2f(0, 0),
                    sf::Color color = sf::Color::Red, 
                    float size = 50);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void rotate();
        void move(sf::Vector2f offset)
        {
            for (auto & block : m_blocks)
                block.move(offset);
        }
        float getSize() { return m_blocks[0].getSize().x; }

};