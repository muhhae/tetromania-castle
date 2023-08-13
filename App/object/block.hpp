#pragma once

#include <SFML/Graphics.hpp>

class Block : public sf::Drawable
{
    private:
        sf::RectangleShape m_shape;
        bool m_active = true;
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
        
        void setActive(bool active = true) { m_active = active; }
        bool getActive() { return m_active; }
};

class BlockCluster : public sf::Drawable
{
        
    public:
        enum class Shape
        {
            rectangle, line, l, l_reverse, t, z, z_reverse, 
            MAX
        };
    private:
        std::vector<Block> m_blocks;
        Shape m_shape;
        float m_size;
        sf::Color m_color;
        sf::Vector2f m_position;
    public:
        BlockCluster() : m_position(sf::Vector2f(0, 0)),
                         m_color(sf::Color::Red),
                         m_shape(Shape::rectangle),
                         m_size(50) {};
        void create();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void rotate();
        void move(sf::Vector2f offset);
        
        BlockCluster& setPosition(sf::Vector2f position) { m_position = position; return *this; }
        BlockCluster& setColor(sf::Color color) { m_color = color; return *this; }
        BlockCluster& setSize(float size) { m_size = size; return *this; }
        BlockCluster& setShape(Shape shape) { m_shape = shape; return *this; }
        
        sf::Vector2f getPosition() { return m_position; }
        sf::Color getColor() { return m_color; }
        Shape getShape() { return m_shape; }
        float getSize() { return m_size; }
        
        sf::Vector2f getBottomPosition();
        std::vector<Block>& getBlocks() { return m_blocks; }
        

};