#include "./AssetManager.h"

AssetManager::AssetManager(EntityManager* manager): manager(manager){

}

void AssetManager::ClearData(){
    textures.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath, SDL_Renderer* renderer){
    textures.emplace(textureId, TextureManager::LoadTexture(filePath, renderer));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId){
    return textures[textureId];
}

