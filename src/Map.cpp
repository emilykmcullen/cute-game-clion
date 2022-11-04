#include "./Game.h"
#include "./Map.h"
#include "./EntityManager.h"
#include <fstream>
#include "./Components/TileComponent.h"
#include "Utils.h"

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
            char nullterminatedChar1[2] = { ch, '\0'};
            int atoiY = atoi(nullterminatedChar1);
            int sourceRectY = atoiY * tileSize;


            mapFile.get(ch);
            char nullterminatedChar2[2] = { ch, '\0'};
            int atoiX = atoi(nullterminatedChar2);
            int sourceRectX = atoiX * tileSize;


            AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
            int b = x * scale * tileSize;
            int c = y * scale * tileSize;

            // Ignore the comma
            mapFile.ignore();

            //Ignore the null terminator at the end of each line
            if (x == mapSizeX - 1)
            {
                mapFile.ignore();
            }
        }
    }
    mapFile.close();
}

void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y){
    //ADD NEW TILE ENTITY IN THE GAME SCENE
    Entity& newTile(manager.AddEntity("Tile", TILEMAP_LAYER, true));
    newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, x, y, tileSize, scale, textureId);
}