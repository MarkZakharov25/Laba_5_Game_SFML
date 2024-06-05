#include "MapManager.h"

MapManager::MapManager(const std::vector<std::string>& mapFiles, const std::string& tilesetFile) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (const auto& mapFile : mapFiles) {
        TileMap map;
        if (map.load(mapFile, tilesetFile)) {
            maps.push_back(map);
        } else {
            std::cerr << "Failed to load map: " << mapFile << std::endl;
        }
    }
}

TileMap& MapManager::getRandomMap() {
    int randomIndex = std::rand() % maps.size();
    return maps[randomIndex];
}
