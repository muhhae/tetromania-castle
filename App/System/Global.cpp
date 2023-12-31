#include "Global.hpp"

#include <map>

sf::Texture& getTexture(const std::string & path)
{
    static std::map<std::string, sf::Texture> textures;
    if (textures.find(path) == textures.end())
    {
        textures[path] = sf::Texture();
        textures[path].loadFromFile(path);
    }
    return textures[path];
}

void initScreen(sf::View & view)
{
    g_screen.bottom = view.getSize().y / 2;
    g_screen.top = view.getSize().y / -2;
    g_screen.left = view.getSize().x / -2;
    g_screen.right = view.getSize().x / 2;
    
    g_screen.width = view.getSize().x;
    g_screen.height = view.getSize().y;
}

sf::Font & getGlobalFont()
{
    static sf::Font font;
    if (font.getInfo().family == "")
        font.loadFromFile(firaFontPath);
    return font;
}

sf::Font & getFont(const std::string& path)
{
    static std::map<std::string, sf::Font> fonts;
    if (fonts.find(path) == fonts.end())
    {
        fonts[path] = sf::Font();
        fonts[path].loadFromFile(path);
    }
    return fonts[path];
}
