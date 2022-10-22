#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL.h>

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);
    static void Draw(SDL_Texture* texture, SDL_Rect source_Rectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip, SDL_Renderer* renderer);
};

#endif