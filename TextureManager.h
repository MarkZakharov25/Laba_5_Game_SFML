#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager {
public:
    bool loadTexture(const std::string& name, const std::string& filename);
    sf::Texture& getTexture(const std::string& name);

private:
    std::unordered_map<std::string, sf::Texture> textures;
};

#endif // TEXTUREMANAGER_H
