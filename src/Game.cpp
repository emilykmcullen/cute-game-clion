#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Entity.h"
#include "./Component.h"
#include "Map.h"




SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Entity* mainPlayer = NULL;
EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
Map* gameMap;

Game::Game(){
    this->isRunning =false;
}

Game::~Game(){

}

bool Game::IsRunning() const {
    return this->isRunning;
}


void Game::Initialize(int width, int height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "Error initializing SDL" << std::endl;
        return;
    }
    if (TTF_Init() !=0) {
        std::cerr << "Error initializing SDL TTF" << std::endl;
    }
    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_SHOWN
    );
    if(!window){
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    isRunning = true;

    //for boxes
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);


    CreateDebugGridRects();

    LoadScene();

    std::cout << "PLAYER POS: " << mainPlayer->GetComponent<TransformComponent>()->position.x << std::endl;
    std::cout << "PLAYER POS: " << mainPlayer->GetComponent<TransformComponent>()->position.y << std::endl;

    return;
}

void Game::LoadScene()
{

    std::string assetId1 = "landscape-tex";
    std::string assetFile1 = "../../assets/test-landscape.png";
    assetManager->AddTexture(assetId1, assetFile1.c_str(), renderer);

    std::string mapTextureId = "landscape-tex";
    std::string mapFile = "../../assets/landscape.map";

    gameMap = new Map(
            mapTextureId,2,
            32);

    gameMap->LoadMap(
            mapFile,
            25,
            20);

    std::string assetId = "player-texture";
    std::string assetFile = "../../assets/monsterspritesheet.png";
    assetManager->AddTexture(assetId, assetFile.c_str(), renderer);

    std::string entityName = "player";
    LayerType entityLayerType = PLAYER_LAYER;

    // Add new entity
    auto& newEntity(manager.AddEntity(entityName, entityLayerType));

    newEntity.AddComponent<TransformComponent>(100, 100, 0, 0, 96, 64, 1);

    // Add sprite component
    std::string textureId = "player-texture";
    bool isAnimated = true;
    if (isAnimated)
    {
        newEntity.AddComponent<SpriteComponent>(textureId, 2, 90, true, false);
    }
    else
    {
        newEntity.AddComponent<SpriteComponent>(textureId, false);
    }

    // Add input control component
    std::string upKey = "w";
    std::string leftKey ="a";
    std::string downKey = "s";
    std::string rightKey = "d";
    std::string shootKey = "space";
    newEntity.AddComponent<KeyboardControlComponent>(upKey, rightKey, downKey, leftKey, shootKey);

    mainPlayer = manager.GetEntityByName("player");

}


//for boxes
void Game::RenderColorBuffer()
{
    //final param is the width of our row
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(WINDOW_WIDTH * sizeof(uint32_t)));
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void Game::DrawRect(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int current_x = x + i;
            int current_y = y + j;
            color_buffer[(WINDOW_WIDTH * current_y) + current_x] = color;
        }
    }
}

void Game::CreateDebugGridRects()
{
    int rectCount = BOXES_PER_ROW_AND_COLUMN * BOXES_PER_ROW_AND_COLUMN;
    int x = 0;
    int y = 0;

    int test = sizeof(SDL_Rect) * rectCount;
    rects = (SDL_Rect*)malloc(test);
    for (int i = 0; i < rectCount; i++)
    {

        SDL_Rect rect = {x, y, 0, 0};
        rect.w = BOX_WIDTH;
        rect.h = BOX_HEIGHT;
        rects[i] = rect;

        // *rects = rect
        // rects++;

        //adds 12
        if (x < WINDOW_WIDTH - BOX_WIDTH)
        {
            x += BOX_WIDTH;
        }
        else
        {
            x = 0;
            y += BOX_HEIGHT;
        }
        std::cout << "X: " << x << ", Y: " << y << std::endl;
    }
}

void Game::ProcessInput(){
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:{
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE){
                isRunning =false;
            }
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            // If mouse is clicked we want to determine if it's an interaction or a movement
            // FOR NOW:
            // If it's on a walkable box then it's a movement, that's all

//            mouseClicked = true;
//            clickX = event.button.x;
//            clickY = event.button.y;




        }
        default: {
            break;
        }
    }
}

void Game::Update(){

    //Sleep the execution until we reach the target frame time in milliseconds
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

    //Only call delay if we are too fast to process this frame
    if(timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME){
        SDL_Delay(timeToWait);
    }

    // delta time is the difference in ticks from the last frame, converted to seconds
    float deltaTime =(SDL_GetTicks() - ticksLastFrame)/1000.0f;

    //Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    //fps
    float avgFPS = frameCount / (( SDL_GetTicks() - ticksLastFrame)/ 1000.f );
    if (avgFPS < 50)
    {
        //std::cout << "FPS: " << avgFPS << std::endl;
    }

    manager.Update(deltaTime);

    HandleCameraMovement();

    frameCount = 0;
    //Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();
    std::cout << "PLAYER POS: " << mainPlayer->GetComponent<TransformComponent>()->position.x << std::endl;
    std::cout << "PLAYER POS: " << mainPlayer->GetComponent<TransformComponent>()->position.y << std::endl;

}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21, 21,21 , 255);
    SDL_RenderClear(renderer);

    SDL_RenderDrawRects(renderer, rects, BOXES_PER_ROW_AND_COLUMN*BOXES_PER_ROW_AND_COLUMN);

    //if(manager.HasNoEntities()){
        //return;
    //}
    manager.Render();

//    RenderColorBuffer();
    SDL_RenderPresent(renderer);
    ++frameCount;
}

void Game::HandleCameraMovement() {
    // camera depends on player position
    // if it's less than 0 on x/y it gets clamped back to 0
    // if it's more than the camera width/height then it gets clamped to width/height

    if (mainPlayer) {
        TransformComponent* mainPlayerTransform = mainPlayer->GetComponent<TransformComponent>();
        camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
        //as soon as player reaches half of the window, only then the camera follows
        camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);
        //clamping camera values so doesnt go offscreen
        camera.x = camera.x < 0 ? 0 : camera.x;
        camera.y = camera.y < 0 ? 0 : camera.y;
        camera.x = camera.x > camera.w ? camera.w : camera.x;
        camera.y = camera.y > camera.h ? camera.h : camera.y;
    }
}


void Game::ProcessGameOver() {
    std::cout << "Game Over" << std::endl;
    isRunning = false;
}


void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}