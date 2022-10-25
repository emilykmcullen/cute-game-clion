#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "AssetManager.h"

class Game {
private:
    bool isRunning;

    SDL_Window *window;


    // Debug visualizations:
    // TO DO: tidy these up elsewhere
    uint32_t* color_buffer = NULL;
    SDL_Texture* color_buffer_texture = NULL;
    void RenderColorBuffer();
    void ClearColorBuffer(uint32_t color);
    void DrawRect(int x, int y, int width, int height, uint32_t color);
    void DrawGrid(uint32_t color, int rectHeight, int rectWidth);
    void DrawSceneBoxes();
    void CreateDebugGridRects();
    SDL_Rect* rects = nullptr;
    //

    void SetPlayerPath();

    int frameCount = 0;

    void LoadScene(int scenenum);



public:
    //TEMPORARY GAME CONSTRUCTOR
    Game();
    ~Game();
    int ticksLastFrame = 0;
    bool IsRunning() const;
    static SDL_Renderer *renderer;
    static AssetManager* assetManager;
    static SDL_Event event;
    static SDL_Rect camera;
    void Initialize(int width, int height);
    void ProcessInput();
    void ProcessGameOver();
    void Update();
    void Render();
    void Destroy();
    void Test();
    void HandleCameraMovement();
    void CheckPlayerCollisions();
};


#endif