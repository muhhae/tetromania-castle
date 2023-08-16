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
