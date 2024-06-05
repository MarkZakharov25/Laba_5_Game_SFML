#pragma once

#ifndef GAME_1_MAPMANAGER_H
#define GAME_1_MAPMANAGER_H


#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "iostream"
#include "TileMap.h"

class MapManager {
public:
    MapManager(const std::vector<std::string>& mapFiles, const std::string& tilesetFile);

    TileMap& getRandomMap();

private:
    std::vector<TileMap> maps;
};

#endif //GAME_1_MAPMANAGER_H
