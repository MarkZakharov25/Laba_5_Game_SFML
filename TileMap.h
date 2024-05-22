#pragma once

#ifndef GAME_1_TILEMAP_H
#define GAME_1_TILEMAP_H


#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

struct TileLayer {
    std::string name;
    int width;
    int height;
    std::vector<int> tiles;
};

struct TileObject {
    std::string name;
    float x;
    float y;
    float width;
    float height;
};

struct TileMapData {
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    std::string tilesetSource;
    std::vector<TileLayer> layers;
    std::vector<TileObject> objects;
};

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string& filename, const std::string& tileset);
    sf::FloatRect getLocalBounds() const;
    const std::vector<TileObject>& getObjects() const;


private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    TileMapData loadTileMap(const std::string& filename);

    std::vector<sf::VertexArray> m_layersVertices;
    sf::Texture m_tileset;
    TileMapData m_tileMapData;
    float scale = 6.75f;
    sf::RectangleShape rect;
};


#endif //GAME_1_TILEMAP_H
