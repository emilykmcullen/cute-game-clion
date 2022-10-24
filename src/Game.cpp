#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Entity.h"
#include "./Component.h"
#include "Map.h"
#include "../lua/sol.hpp"





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

    LoadScene(1);

    //std::cout << "PLAYER POS: " << mainPlayer->GetComponent<TransformComponent>()->position.x << std::endl;
    //std::cout << "PLAYER POS: " << mainPlayer->GetComponent<TransformComponent>()->position.y << std::endl;

    return;
}

void Game::LoadScene(int scenenum)
{

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    //these libraries are now available to me

    std::string levelName = "Scene" + std::to_string(scenenum);
    lua.script_file("../../assets/scripts/" + levelName + ".lua");

    /***************************************************/
    /* LOAD ASSETS FROM LUA CONFIG FILE */
    /***************************************************/

    sol::table levelData = lua[levelName];
    sol::table levelAssets = levelData["assets"];
    //will make a table of all the data in the file

    unsigned int assetIndex = 0;
    while (true) {
        sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
        //while loop will run until index of assets doesnt exist
        if (existsAssetIndexNode == sol::nullopt) {
            break;
        } else {
            sol::table asset = levelAssets[assetIndex];
            std::string assetType = asset["type"];
            if ( assetType.compare("texture") == 0) {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                assetManager->AddTexture(assetId, assetFile.c_str(), renderer);
            }
        }
        assetIndex++;
    }

    /***************************************************/
    /* LOADS MAP FROM LUA CONFIG FILE */
    /***************************************************/

    sol::table levelMap = levelData["map"];
    std::string mapTextureId = levelMap["textureAssetId"];
    std::string mapFile = levelMap["file"];
    std::cout << "MAPTEXID: " << mapTextureId << std::endl;

    gameMap = new Map(
            mapTextureId,
            static_cast<int>(levelMap["scale"]),
            static_cast<int>(levelMap["tileSize"])
    );

    gameMap->LoadMap(
            mapFile,
            static_cast<int>(levelMap["mapSizeX"]),
            static_cast<int>(levelMap["mapSizeY"])
    );

    /***************************************************/
    /* LOADS ENTITIES AND COMPONENTS FROM LUA CONFIG FILE */
    /***************************************************/

    sol::table levelEntities = levelData["entities"];
    unsigned int entityIndex = 0;
    while (true) {
        sol::optional<sol::table> existsEntityIndexNode = levelEntities[entityIndex];
        if (existsEntityIndexNode == sol::nullopt) {
            break;
        }
        else {
            sol::table entity = levelEntities[entityIndex];
            std::string entityName = entity["name"];
            LayerType entityLayerType = static_cast<LayerType>(static_cast<int>(entity["layer"]));

            // Add new entity
            auto& newEntity(manager.AddEntity(entityName, entityLayerType));

            // Add Transform Component
            sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];
            if (existsTransformComponent != sol::nullopt) {
                newEntity.AddComponent<TransformComponent>(
                        static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                        static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                        static_cast<int>(entity["components"]["transform"]["velocity"]["x"]),
                        static_cast<int>(entity["components"]["transform"]["velocity"]["y"]),
                        static_cast<int>(entity["components"]["transform"]["width"]),
                        static_cast<int>(entity["components"]["transform"]["height"]),
                        static_cast<int>(entity["components"]["transform"]["scale"])
                );
            }

            // Add sprite component
            sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];
            if (existsSpriteComponent != sol::nullopt) {
                std::string textureId = entity["components"]["sprite"]["textureAssetId"];
                bool isAnimated = entity["components"]["sprite"]["animated"];
                if (isAnimated) {
                    newEntity.AddComponent<SpriteComponent>(
                            textureId,
                            static_cast<int>(entity["components"]["sprite"]["frameCount"]),
                            static_cast<int>(entity["components"]["sprite"]["animationSpeed"]),
                            static_cast<bool>(entity["components"]["sprite"]["hasDirections"]),
                            static_cast<bool>(entity["components"]["sprite"]["fixed"])
                    );
                } else {
                    newEntity.AddComponent<SpriteComponent>(textureId, false);
                }
            }

            // Add input control component
            sol::optional<sol::table> existsInputComponent = entity["components"]["input"];
            if (existsInputComponent != sol::nullopt) {
                sol::optional<sol::table> existsKeyboardInputComponent = entity["components"]["input"]["keyboard"];
                if (existsKeyboardInputComponent != sol::nullopt) {
                    std::string upKey = entity["components"]["input"]["keyboard"]["up"];
                    std::string rightKey = entity["components"]["input"]["keyboard"]["right"];
                    std::string downKey = entity["components"]["input"]["keyboard"]["down"];
                    std::string leftKey = entity["components"]["input"]["keyboard"]["left"];
                    std::string shootKey = entity["components"]["input"]["keyboard"]["shoot"];
                    newEntity.AddComponent<KeyboardControlComponent>(upKey, rightKey, downKey, leftKey, shootKey);
                }
            }
        }
        entityIndex++;
    }
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
        //std::cout << "X: " << x << ", Y: " << y << std::endl;
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
    //std::cout << "PLAYER POS: " << mainPlayer->GetComponent<TransformComponent>()->position.x << std::endl;
    //std::cout << "PLAYER POS: " << mainPlayer->GetComponent<TransformComponent>()->position.y << std::endl;

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