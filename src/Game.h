#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Map.h"

#include "AssetManager.h"

class Game {
private:
    bool isRunning;

    SDL_Window *window;

    int frameCount = 0;

    void LoadScene(int scenenum);



public:
    //TEMPORARY GAME CONSTRUCTOR
    Game();
    ~Game();
    int ticksLastFrame = 0;
    bool IsRunning() const;
    static SDL_Renderer *renderer;
    static AssetManager *assetManager;
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
    static int scroll;
};


#endif