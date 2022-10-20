//
// Created by Emily Cullen on 20/10/2022.
//

#ifndef SDL2_BASIC_SETUP_SPRITECOMPONENT_H
#define SDL2_BASIC_SETUP_SPRITECOMPONENT_H

#include "SDL.h"
#include "SDL_image.h"
#include "Constants.h"
#include <string>

// DECIDED TO DO THIS LATER, FOR NOW I JUST WANT TO GET A PLAYER SPRITE RENDERING IN V SIMPLE WAY
class SpriteComponent
{
private:
    SDL_Texture* texture;

public:

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;

    void Initialize(float x, float y, float width, float height, const char* spriteFile, SDL_Renderer* renderer)
    {
        SDL_Surface* surface = IMG_Load(spriteFile);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        sourceRectangle.x = x;
        sourceRectangle.y = y;
        sourceRectangle.w = width;
        sourceRectangle.h = height;
        destinationRectangle.x = x;
        destinationRectangle.y = y;
        destinationRectangle.w = width;
        destinationRectangle.h = height;
    }

    void Render(SDL_Renderer* renderer)
    {
        SDL_RenderCopyEx(renderer, texture, &sourceRectangle, &destinationRectangle, 0.0, NULL, SDL_FLIP_NONE);
    }
};


#endif //SDL2_BASIC_SETUP_SPRITECOMPONENT_H
