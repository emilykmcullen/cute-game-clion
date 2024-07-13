#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/MovementScheduleComponent.h"
#include "./Components/InteractionComponent.h"
#include "./Components/TextLabelComponent.h"
#include "./Entity.h"
#include "./Component.h"

#include "../lua/sol.hpp"
#include "Utils.h"

SDL_Renderer* Game::renderer;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
SDL_Cursor *cursor = NULL;
SDL_Cursor *cursorlarge = NULL;
SDL_Cursor *cursorlargegrey = NULL;
Entity* mainPlayer = NULL;
EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
Map* gameMap;
int Game::scroll = 1;
bool Game::suspendMovement = false;

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
            SDL_WINDOW_BORDERLESS
    );
    if(!window){
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    if(!renderer){
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    InitializeCursors();

    isRunning = true;

    LoadScene(1);

    return;
}

void Game::InitializeCursors()
{
    // Regular cursor
    SDL_Surface* surface = IMG_Load("../../assets/cursor.png");
    cursor = SDL_CreateColorCursor(surface, 0, 0);
    SDL_SetCursor(cursor);
    SDL_FreeSurface(surface);

    // Large cursor
    SDL_Surface* surfacelarge = IMG_Load("../../assets/cursorlarge.png");
    cursorlarge = SDL_CreateColorCursor(surfacelarge, 0, 0);
    SDL_FreeSurface(surfacelarge);

    // Large greyed out cursor
    SDL_Surface* surfacelargegrey = IMG_Load("../../assets/cursorlargegrey.png");
    cursorlargegrey = SDL_CreateColorCursor(surfacelargegrey, 0, 0);
    SDL_FreeSurface(surfacelargegrey);
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

            if (assetType.compare("font") == 0) {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                int fontSize = asset["fontSize"];
                assetManager->AddFont(assetId, assetFile.c_str(), fontSize);
            }
        }
        assetIndex++;
    }

    /***************************************************/
    /* LOADS MAP FROM LUA CONFIG FILE */
    /***************************************************/

    sol::table levelMap = levelData["map"];
    std::string mapTextureId = levelMap["textureAssetId"];
    std::cout << "MAPTEXID: " << mapTextureId << std::endl;
    scroll = levelMap["scroll"];
    camera.w = WINDOW_WIDTH * scroll;
    camera.h = WINDOW_HEIGHT * scroll;

    gameMap = new Map(
            mapTextureId,
            static_cast<int>(levelMap["scale"]),
            static_cast<int>(levelMap["tileSize"])
    );

    gameMap->LoadMap(
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
            bool isActive = entity["isActive"];

            // Add new entity
            auto& newEntity(manager.AddEntity(entityName, entityLayerType, isActive));

            // Add Transform Component
            sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];
            if (existsTransformComponent != sol::nullopt) {
                bool isCentered = entity["components"]["transform"]["centered"];
                bool canGoOffscreen = entity["components"]["transform"]["offscreen"];
                newEntity.AddComponent<TransformComponent>(
                        static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                        static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                        static_cast<int>(entity["components"]["transform"]["velocity"]["x"]),
                        static_cast<int>(entity["components"]["transform"]["velocity"]["y"]),
                        static_cast<int>(entity["components"]["transform"]["width"]),
                        static_cast<int>(entity["components"]["transform"]["height"]),
                        static_cast<float>(entity["components"]["transform"]["scale"]),
                        isCentered,
                        canGoOffscreen

                );
            }

            // Add collider component
            sol::optional<sol::table> existsColliderComponent = entity["components"]["collider"];
            if (existsColliderComponent != sol::nullopt) {
                std::string colliderTag = entity["components"]["collider"]["tag"];
                std::string resultOfCollision = entity["components"]["collider"]["result"];
                bool isSpecialSize = entity["components"]["collider"]["specialSize"];
                if (isSpecialSize)
                {
                    newEntity.AddComponent<ColliderComponent>(
                            colliderTag,
                            static_cast<int>(entity["components"]["collider"]["x"]),
                            static_cast<int>(entity["components"]["collider"]["y"]),
                            static_cast<int>(entity["components"]["collider"]["width"]),
                            static_cast<int>(entity["components"]["collider"]["height"]),
                            static_cast<int>(entity["components"]["transform"]["scale"]),
                            resultOfCollision
                    );
                }
                else
                {
                    newEntity.AddComponent<ColliderComponent>(
                            colliderTag,
                            static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                            static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                            static_cast<int>(entity["components"]["transform"]["width"]),
                            static_cast<int>(entity["components"]["transform"]["height"]),
                            static_cast<int>(entity["components"]["transform"]["scale"]),
                            resultOfCollision
                    );
                }

            }

            // Add sprite component
            sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];
            if (existsSpriteComponent != sol::nullopt) {
                std::string textureId = entity["components"]["sprite"]["textureAssetId"];
                bool isAnimated = entity["components"]["sprite"]["animated"];
                bool isAnimatedWhileNotMoving = entity["components"]["sprite"]["animatedWhileNotMoving"];
                bool hasCollisionAnim = entity["components"]["sprite"]["hasCollisionAnim"];
                if (isAnimated) {
                    newEntity.AddComponent<SpriteComponent>(
                            textureId,
                            static_cast<int>(entity["components"]["sprite"]["frameCount"]),
                            static_cast<int>(entity["components"]["sprite"]["animationSpeed"]),
                            static_cast<bool>(entity["components"]["sprite"]["hasDirections"]),
                            static_cast<bool>(entity["components"]["sprite"]["fixed"]),
                            isAnimatedWhileNotMoving,
                            hasCollisionAnim
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

            // Add MovementScheduleComponent
            sol::optional<sol::table> existsMovementScheduleComponent = entity["components"]["movementschedule"];
            if (existsMovementScheduleComponent != sol::nullopt) {


                sol::table destinationVectors = entity["components"]["movementschedule"]["destinations"];
                //will make a table of the destinations
                std::vector<vec2> destinations;
                unsigned int destinationsIndex = 0;
                while (true) {
                    sol::optional<sol::table> existsAssetIndexNode = destinationVectors[destinationsIndex];
                    //while loop will run until index of destinations doesnt exist
                    if (existsAssetIndexNode == sol::nullopt) {
                        break;
                    } else {
                        sol::table destination = destinationVectors[destinationsIndex];
                        float x = static_cast<float>(destination["x"]);
                        float y = static_cast<float>(destination["y"]);
                        vec2 vec = { x, y};
                        destinations.push_back(vec);
                    }
                    destinationsIndex++;
                }

                int timeAtDestination = static_cast<int>(entity["components"]["movementschedule"]["timeAtDestination"]);
                newEntity.AddComponent<MovementScheduleComponent>(destinations, timeAtDestination);
            }

            // Add interaction component
            sol::optional<sol::table> existsInteractionComponent = entity["components"]["interaction"];
            if (existsInteractionComponent != sol::nullopt) {
                InteractionType interactionType1 = InteractionType::NO_INTERACTION;
                std::string interactionType2 = entity["components"]["interaction"]["interactiontype"];
                if (interactionType2 == "loadscene")
                {
                    interactionType1 = InteractionType::LOAD_SCENE;
                }
                else if (interactionType2 == "speak")
                {
                    interactionType1 = InteractionType::SPEAK;
                }
                else if (interactionType2 == "deactivate")
                {
                    interactionType1 = InteractionType::DEACTIVATE;
                }
                std::string info = entity["components"]["interaction"]["info"];
                int clickAllowance = entity["components"]["interaction"]["clickAllowance"];
                sol::optional<sol::table> existsRectComponent = entity["components"]["interaction"]["rect"];
                if (existsRectComponent)
                {
                    int x = static_cast<int>(entity["components"]["interaction"]["rect"]["x"]);
                    int y = static_cast<int>(entity["components"]["interaction"]["rect"]["y"]);
                    int width = static_cast<int>(entity["components"]["interaction"]["rect"]["width"]);
                    int height = static_cast<int>(entity["components"]["interaction"]["rect"]["height"]);
                    newEntity.AddComponent<InteractionComponent>(interactionType1, info, x, y, width, height, clickAllowance);
                }
                else
                {
                    newEntity.AddComponent<InteractionComponent>(interactionType1, info, clickAllowance);
                }


            }

            // Add text lbale component
            sol::optional<sol::table> existsTextLabelComponent = entity["components"]["textlabel"];
            if (existsTextLabelComponent != sol::nullopt) {
                    int x = entity["components"]["textlabel"]["x"];
                    int y = entity["components"]["textlabel"]["y"];
                    std::string text = entity["components"]["textlabel"]["text"];
                    std::string font = entity["components"]["textlabel"]["font"];
                    SDL_Color col = { 0, 0, 0};
                    bool background = entity["components"]["textlabel"]["background"];
                    if (background)
                    {
                        SDL_Color backcol = { 255, 255, 255};
                        newEntity.AddComponent<TextLabelComponent>(x, y, text, font, col, backcol);
                    }
                    else
                    {
                        newEntity.AddComponent<TextLabelComponent>(x, y, text, font, col);
                    }
            }
        }
        entityIndex++;
    }
    mainPlayer = manager.GetEntityByName("player");
}

void Game::ProcessInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type){
            case SDL_QUIT:{
                isRunning = false;
                continue;
            }
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    isRunning = false;
                    continue;
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                interaction interaction1 = manager.CheckIfClickedOnEntity(event.button.x, event.button.y);
                HandleInteraction(interaction1);
                if (interaction1.interactionType != InteractionType::NO_INTERACTION) {
                    continue;
                }
                break;
            }
            default: {
                break;
            }
        }

        manager.HandleEvent(event);
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
//    float avgFPS = frameCount / (( SDL_GetTicks() - ticksLastFrame)/ 1000.f );
//    if (avgFPS < 60)
//    {
//        std::cout << "FPS: " << avgFPS << std::endl;
//    }

    UpdateCursor();

    manager.Update(deltaTime);

    HandleCameraMovement();

    frameCount = 0;
    //Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

}

void Game::UpdateCursor()
{
    int x, y;
    Uint32 buttons;
    //SDL_PumpEvents();  // make sure we have the latest mouse state.
    buttons = SDL_GetMouseState(&x, &y);
    CursorType cursorType = manager.IsCursorOverInteractionRect(x,y);
    if (cursorType == CursorType::LARGE)
    {
        SDL_SetCursor(cursorlarge);
    }
    else if (cursorType == CursorType::REGULAR)
    {
        SDL_SetCursor(cursor);
    }
    else
    {
        SDL_SetCursor(cursorlargegrey);
    }
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21, 21,21 , 255);
    SDL_RenderClear(renderer);

    //if(manager.HasNoEntities()){
        //return;
    //}
    manager.Render();

    SDL_RenderPresent(renderer);
    ++frameCount;
}

void Game::HandleCameraMovement() {
    // camera depends on player position
    // if it's less than 0 on x/y it gets clamped back to 0
    // if it's more than the camera width/height then it gets clamped to width/height

    if (mainPlayer ) {
        if (Game::scroll > 1)
        {
            TransformComponent* mainPlayerTransform = mainPlayer->GetComponent<TransformComponent>();
            camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
            camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

            //as soon as player reaches half of the window, only then the camera follows

            //clamping camera values so doesnt go offscreen
            camera.x = camera.x < 0 ? 0 : camera.x;
            camera.y = camera.y < 0 ? 0 : camera.y;
            camera.x = camera.x > camera.w - (camera.w/Game::scroll) ? camera.w - (camera.w/Game::scroll): camera.x;
            camera.y = camera.y > camera.h - (camera.h/Game::scroll) ? camera.h - (camera.h/Game::scroll) : camera.y;
        }
        else
        {
            camera.x = 0;
            camera.y = 0;
        }

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

void Game::HandleInteraction(interaction interaction)
{
    if (interaction.interactionType == InteractionType::LOAD_SCENE)
    {
        assetManager->ClearData();
        manager.ClearData();
        int i = std::stoi(interaction.info);
        LoadScene(i);
    }
    else if (interaction.interactionType == InteractionType::SPEAK)
    {
        Entity* entity = manager.GetEntityByName(interaction.info);
        entity->Activate();
        suspendMovement = true;
    }
    else if (interaction.interactionType == InteractionType::DEACTIVATE)
    {
        manager.GetEntityByName(interaction.info)->Deactivate();
        suspendMovement = false;
    }

}