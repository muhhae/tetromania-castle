#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

#include "Global.hpp"

class Button : public sf::Drawable
{
public:
    Button() {}
    
    Button& setOrigin(sf::Vector2f origin) {m_button.setOrigin(origin); return *this;}
    Button& setButtonPosition(sf::Vector2f position) {m_button.setPosition(position); return *this;}
    Button& setButtonSize(sf::Vector2f size) {m_button.setSize(size); return *this;}
    Button& setButtonColor(sf::Color color) {m_button.setFillColor(color); return *this;}
    Button& setButtonOutlineColor(sf::Color color) {m_button.setOutlineColor(color); return *this;}
    Button& setButtonOutlineThickness(float thickness) {m_button.setOutlineThickness(thickness); return *this;}
    
    Button& setFont(sf::Font font) {m_font = font; return *this;}
    Button& setTextString(std::string string) {m_text.setString(string); return *this;}
    Button& setTextSize(unsigned int size) {m_text.setCharacterSize(size); return *this;}
    Button& setTextColor(sf::Color color) {m_text.setFillColor(color); return *this;}
    Button& setTextPosition(sf::Vector2f position) {m_text.setPosition(position); return *this;}
    
    Button& setButtonOnClick(std::function<void()> functionOnClick) {m_onClick = functionOnClick; return *this;}
    Button& setButtonOnHover(std::function<void()> functionOnHover) {m_onHover = functionOnHover; return *this;}
    
    void update(const sf::RenderWindow & window)
    {
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (m_button.getGlobalBounds().contains(mousePosition) && m_onHover)
        {
            m_onHover();
        }
        
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            isMouseDown = false;
        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) 
            && m_button.getGlobalBounds().contains(mousePosition)
            && m_onClick)
        {
            if (!isMouseDown)
            {
                m_onClick();
                isMouseDown = true;
            }
        }
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_button);
        target.draw(m_text);
    }
private:
    sf::RectangleShape m_button = sf::RectangleShape(sf::Vector2f(100, 50));
    sf::Text m_text = sf::Text("Button", g_font, 20);
    sf::Font m_font;
    
    std::function<void()> m_onClick;
    std::function<void()> m_onHover;
    
    static bool isMouseDown;
};

bool Button::isMouseDown = false;

