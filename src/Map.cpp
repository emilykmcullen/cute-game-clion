#include "./Game.h"
#include "./Map.h"
#include "./EntityManager.h"
#include <fstream>
#include "./Components/TileComponent.h"

extern EntityManager manager;

Map::Map(std::string textureId, int scale, int tileSize){
    this->textureId = textureId;
    this->scale = scale;
    this->tileSize = tileSize;
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY){
    // READ THE MAP TILE DEFINITIONS FROM THE .map FILE
    std::fstream mapFile;
    mapFile.open(filePath);

    //y for rows, x for columns in the file
    //for each row, and for inside each row each column get the character one by one
    //after getting the char convert from string to int and times by the tile size (32)
    for (int y = 0; y < mapSizeY; y++) {
        for (int x = 0; x < mapSizeX; x++) {
            char ch;
            mapFile.get(ch);
            //eg. if ch is '01' convert 1
            // sourceRectY = 1 * tilesize (32)
            // sourceRectY = 32
            int sourceRectY = atoi(&ch) * tileSize;
            mapFile.get(ch);
            int sourceRectX = atoi(&ch) * tileSize;
            //std::cout << "x: " << x << ", y: " << y << std::endl;
            AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
            //std::cout << "SOURCE X: " << sourceRectX << ", SOURCE Y: " << sourceRectY << std::endl;
            int b = x * scale * tileSize;
            int c = y * scale * tileSize;
            //std::cout << "DEST X: " << b << ", DEST Y: " << c << std::endl;
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y){
    //ADD NEW TILE ENTITY IN THE GAME SCENE
    Entity& newTile(manager.AddEntity("Tile", TILEMAP_LAYER, true));
    newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, x, y, tileSize, scale, textureId);
}