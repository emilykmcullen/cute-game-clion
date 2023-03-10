
#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "../FontManager.h"
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Game.h"


class TextLabelComponent: public Component {
private:
    SDL_Rect position;
    std::string text;
    std::string fontFamily;
    SDL_Color color;
    SDL_Texture* texture;
    bool background = false;
    SDL_Rect backgroundRect;
public:
    TextLabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color& color) {
        this->position.x = x;
        this->position.y = y;
        this->text = text;
        this->fontFamily = fontFamily;
        this->color = color;
        SetLabelText(text, fontFamily);
    }

    TextLabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color& color, const SDL_Color& backcolor) {
        this->position.x = x;
        this->position.y = y;
        this->text = text;
        this->fontFamily = fontFamily;
        this->color = color;
        background = true;
        this->backgroundRect.x = x - 4;
        this->backgroundRect.y = y - 4;
        this->backgroundRect.w = 512; //just hardcoding for moment, TO DO: change this
        this->backgroundRect.h = 128;
        SetLabelText(text, fontFamily);
    }

    void SetLabelText(std::string text, std::string fontFamily) {
        //this will receive the font family, get the font family from the asset manager and then pass the label
        //pretty much all text with SDL must be converted to a c-style string
        SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager->GetFont(fontFamily), text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
        //deletes/frees the memory where the surface is (prevents memory leak)
        SDL_FreeSurface(surface);
        //retrieves the basic settings of a texture (texture, &format, &access, &width, &height)
        SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    }

    void Render() override {

        //TO DO: Temp for background rect, sort it out later
        if (background)
        {
            // Set render color to blue ( rect will be rendered in this color )
            SDL_SetRenderDrawColor( Game::renderer, 255, 255, 255, 255 );

            // Render rect
            SDL_RenderFillRect( Game::renderer, &backgroundRect );

        }
        FontManager::Draw(texture, position);
    }

    void Update(float deltaTime) override {
        if (owner->name == "timer")
        {

        }
    }
};