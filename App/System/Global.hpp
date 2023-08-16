#pragma once

#include <string>
#include <SFML/Graphics.hpp>

const static std::string g_resourcePath = "Resources/";

const static std::string g_fontPath = g_resourcePath + "Fonts/";
const static std::string g_backgroundPath = g_resourcePath + "Backgrounds/"; 
const static std::string g_blockPath = g_resourcePath + "Blocks/"; 
const static std::string g_UIPath = g_resourcePath + "UI/";
const static std::string g_buttonPath = g_UIPath + "Buttons/";

const std::string firaFontPath = g_fontPath + "firaFont.ttf";
const std::string castleBackgroundPath = g_backgroundPath + "castle.jpg";
const std::string blockTexturePath = g_blockPath + "brick_1.png";
const std::string buttonTexturePath = g_buttonPath + "button.png";
const std::string buttonOnHoverTexturePath = g_buttonPath + "button_on_hover.png";
const std::string pauseButtonTexturePath = g_buttonPath + "pause_1.png";


struct GameScreen 
{
    int width;
    int height;
    int top, bottom, left, right;
};

inline GameScreen g_screen;
inline sf::Font g_font;

sf::Texture& getTexture(const std::string & path);




