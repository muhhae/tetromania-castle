#pragma once
#include <string>
#include <SFML/Graphics.hpp>

const static std::string g_resourcePath = "Resources/";
const static std::string g_fontPath = g_resourcePath + "Fonts/";
const static std::string g_backgroundPath = g_resourcePath + "Backgrounds/"; 
const static std::string g_blockPath = g_resourcePath + "Blocks/"; 

const static std::string g_selectedFont = g_fontPath + "firaFont.ttf";
const static std::string g_selectedBackground = g_backgroundPath + "castle.jpg";
const static std::string g_selectedBlock = g_blockPath + "brick_1.png";

struct GameScreen 
{
    int width;
    int height;
    int top, bottom, left, right;
};

inline GameScreen g_screen;
inline sf::Font g_font;
