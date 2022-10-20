#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Scene.h"
#include "Player.h"


class Game {
private:
    bool isRunning;
    bool mouseClicked = false;
    int clickX;
    int clickY;

    SDL_Window *window;
    Scene* my_scene;
    Player my_player;


    // Debug visualizations:
    // TO DO: tidy these up elsewhere
    uint32_t* color_buffer = NULL;
    SDL_Texture* color_buffer_texture = NULL;
    void RenderColorBuffer();
    void ClearColorBuffer(uint32_t color);
    void DrawRect(int x, int y, int width, int height, uint32_t color);
    void DrawGrid(uint32_t color, int rectHeight, int rectWidth);
    void DrawSceneBoxes();
    void SetPlayerPath();
    //

    int frameCount = 0;

public:
    //TEMPORARY GAME CONSTRUCTOR
    Game();
    ~Game();
    int ticksLastFrame = 0;
    bool IsRunning() const;
    static SDL_Renderer *renderer;
    static SDL_Event event;
    void Initialize(int width, int height);
    void ProcessInput();
    void ProcessGameOver();
    void Update();
    void Render();
    void Destroy();
    void Test();
};


#endif