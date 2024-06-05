#include "TileMap.h"
#include <iostream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include <limits>
#include <algorithm>

TileMapData TileMap::loadTileMap(const std::string& filename) {
    TileMapData tileMap;
    XMLDocument doc;

    if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
        std::cerr << "Error loading file: " << filename << std::endl;
        return tileMap;
    }

    XMLElement* mapElement = doc.FirstChildElement("map");
    if (!mapElement) {
        std::cerr << "No <map> element found!" << std::endl;
        return tileMap;
    }

    mapElement->QueryIntAttribute("width", &tileMap.width);
    mapElement->QueryIntAttribute("height", &tileMap.height);
    mapElement->QueryIntAttribute("tilewidth", &tileMap.tileWidth);
    mapElement->QueryIntAttribute("tileheight", &tileMap.tileHeight);

    XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
    if (tilesetElement) {
        const char* source = tilesetElement->Attribute("source");
        if (source) {
            tileMap.tilesetSource = source;
        }
    }

    XMLElement* layerElement = mapElement->FirstChildElement("layer");
    while (layerElement) {
        TileLayer layer;
        layer.name = layerElement->Attribute("name");
        layerElement->QueryIntAttribute("width", &layer.width);
        layerElement->QueryIntAttribute("height", &layer.height);

        XMLElement* dataElement = layerElement->FirstChildElement("data");
        if (dataElement) {
            const char* csvData = dataElement->GetText();
            if (csvData) {
                std::string dataStr(csvData);
                std::stringstream ss(dataStr);
                std::string tile;

                while (std::getline(ss, tile, ',')) {
                    layer.tiles.push_back(std::stoi(tile));
                }
            }
        }

        tileMap.layers.push_back(layer);
        layerElement = layerElement->NextSiblingElement("layer");
    }

    XMLElement* objectGroupElement = mapElement->FirstChildElement("objectgroup");
    while (objectGroupElement) {
        XMLElement* objectElement = objectGroupElement->FirstChildElement("object");
        while (objectElement) {
            TileObject object;
            objectElement->QueryFloatAttribute("x", &object.x);
            objectElement->QueryFloatAttribute("y", &object.y);
            objectElement->QueryFloatAttribute("width", &object.width);
            objectElement->QueryFloatAttribute("height", &object.height);

            object.x *= scale;
            object.y *= scale;
            object.width *= scale;
            object.height *= scale;

            if (const char* name = objectElement->Attribute("name")) {
                object.name = name;
            }

            tileMap.objects.push_back(object);
            objectElement = objectElement->NextSiblingElement("object");
        }

        objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
    }

    return tileMap;
}

bool TileMap::load(const std::string& filename, const std::string& tileset) {
    m_tileMapData = loadTileMap(filename);

    if (!m_tileset.loadFromFile(tileset)) {
        return false;
    }

    m_layersVertices.clear();
    m_layersVertices.resize(m_tileMapData.layers.size());

    for (size_t layerIndex = 0; layerIndex < m_tileMapData.layers.size(); ++layerIndex) {
        const auto& layer = m_tileMapData.layers[layerIndex];
        sf::VertexArray& vertices = m_layersVertices[layerIndex];

        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(layer.width * layer.height * 4);

        for (int i = 0; i < layer.width; ++i) {
            for (int j = 0; j < layer.height; ++j) {
                int tileNumber = layer.tiles[i + j * layer.width];
                if (tileNumber == 0) {
                    continue;
                }

                int tu = (tileNumber - 1) % (m_tileset.getSize().x / m_tileMapData.tileWidth);
                int tv = (tileNumber - 1) / (m_tileset.getSize().x / m_tileMapData.tileWidth);

                sf::Vertex* quad = &vertices[(i + j * layer.width) * 4];

                quad[0].position = sf::Vector2f(i * m_tileMapData.tileWidth, j * m_tileMapData.tileHeight);
                quad[1].position = sf::Vector2f((i + 1) * m_tileMapData.tileWidth, j * m_tileMapData.tileHeight);
                quad[2].position = sf::Vector2f((i + 1) * m_tileMapData.tileWidth, (j + 1) * m_tileMapData.tileHeight);
                quad[3].position = sf::Vector2f(i * m_tileMapData.tileWidth, (j + 1) * m_tileMapData.tileHeight);

                quad[0].texCoords = sf::Vector2f(tu * m_tileMapData.tileWidth, tv * m_tileMapData.tileHeight);
                quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileMapData.tileWidth, tv * m_tileMapData.tileHeight);
                quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileMapData.tileWidth, (tv + 1) * m_tileMapData.tileHeight);
                quad[3].texCoords = sf::Vector2f(tu * m_tileMapData.tileWidth, (tv + 1) * m_tileMapData.tileHeight);
            }
        }
    }

    return true;
}

sf::FloatRect TileMap::getLocalBounds() const {
    if (m_layersVertices.empty()) {
        return sf::FloatRect();
    }

    float width = 0;
    float height = 0;

    for (const auto& layer : m_layersVertices) {
        if (!layer.getBounds().width || !layer.getBounds().height) {
            continue;
        }
        width = std::max(width, layer.getBounds().width);
        height = std::max(height, layer.getBounds().height);
    }

    return sf::FloatRect(0, 0, width, height);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_tileset;

    for (const auto& vertices : m_layersVertices) {
        target.draw(vertices, states);
    }
}

const std::vector<TileObject>& TileMap::getObjects() const {
    return m_tileMapData.objects;
}

const std::vector<TileLayer>& TileMap::getLayers() const {
    return m_tileMapData.layers;
}

int TileMap::getTileWidth() const {
    return m_tileMapData.tileWidth;
}

int TileMap::getTileHeight() const {
    return m_tileMapData.tileHeight;
}

const sf::Texture& TileMap::getTileset() const {
    return m_tileset;
}

std::vector<sf::Vector2f> TileMap::getSpawnPositions(const std::string& objectName) const {
    std::vector<sf::Vector2f> positions;
    for (const auto& object : m_tileMapData.objects) {
        if (object.name == objectName) {
            positions.emplace_back(object.x, object.y);
        }
    }
    return positions;
}