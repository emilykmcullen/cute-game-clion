#include <iostream>
#include "./Constants.h"
#include "./Game.h"

SDL_Renderer* Game::renderer;
SDL_Event Game::event;

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
    my_scene = new Scene("emily sceene");
    std::vector<int> nonwalkboxes = { 42,43,44, 70, 71, 73, 74, 75, 76, 77, 79};
    my_scene->NonWalkableBoxes(nonwalkboxes);
    my_player.Initialize(0,0, "../../assets/spottydog.png", renderer); //path in relation to where i output the exe
    my_scene->Initialize("../../assets/landscape.png", renderer);
    my_player.m_scene = my_scene;

    //my_scene->PrintBoxInfo();
    //Test();

    return;
}

// void Game::Test()
// {
//     TreeNode* currentNode = my_scene->FindPath(4, 11);
//     if (currentNode != nullptr)
//     {
//         while(currentNode->parent != nullptr)
//         {
//             std::cout << currentNode->data << std::endl;
//             currentNode = currentNode->parent;
//         }
//         std::cout << currentNode->data << std::endl;
//     }

//     my_scene->DeletePath();

// }

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

void Game::DrawGrid(uint32_t color, int rectHeight, int rectWidth) {
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        if (y % rectHeight == 0) {
            for (int x = 0; x < WINDOW_WIDTH; x++) {
                color_buffer[(WINDOW_WIDTH * y) + x] = color;
            }
        } else {
            for (int x = 0; x < WINDOW_WIDTH; x += rectWidth) {
                color_buffer[(WINDOW_WIDTH * y) + x] = color;
            }
        }
    }
}

void Game::DrawSceneBoxes()
{
    uint32_t colour = 0x0000FF00;
//    for (int i = 0; i < BOXES_PER_ROW_AND_COLUMN * BOXES_PER_ROW_AND_COLUMN; i++)
//    {
//        scene_box* box = my_scene->boxes.at(i);
//        DrawRect(box->originX, box->originY, BOX_WIDTH, BOX_HEIGHT, colour);
//        colour = (uint32_t) ((float)colour / 1.04f);
//    }

    DrawGrid(colour, BOX_HEIGHT, BOX_WIDTH);

    //temporary for testing
    //uint32_t playerBox = 0x00FFFFFF;
    //DrawRect(my_player.m_position.x, my_player.m_position.y, BOX_WIDTH/5, BOX_HEIGHT/5, playerBox);

    //colour obstacles, temporary for testing
//    for (int i = 0; i < BOXES_PER_ROW_AND_COLUMN * BOXES_PER_ROW_AND_COLUMN; i++)
//    {
//        scene_box* box = my_scene->GetBoxById(i);
//        if (box->walkable_status == walkable::NOT_WALKABLE) {
//            uint32_t obstaclecolour = 0x00FF0000;
//            DrawRect(box->originX, box->originY, BOX_WIDTH, BOX_HEIGHT, obstaclecolour);
//        }
//    }

}

void Game::ClearColorBuffer(uint32_t color)
{
    for (int i = 0; i < (WINDOW_WIDTH * WINDOW_HEIGHT); i++)
    {
        color_buffer[i] = color;
    }

    // for (int y = 0; y < window_height; y++)
    // {
    //     for (int x = 0; x < window_width; x++)
    //     {
    //         color_buffer[(window_width * y) + x] = color;
    //     }
    // }
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

            mouseClicked = true;
            clickX = event.button.x;
            clickY = event.button.y;




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
        std::cout << "FPS: " << avgFPS << std::endl;
    }

    frameCount = 0;


    // Have we clicked the mouse this loop?
    if (mouseClicked)
    {
        // Was the mouse clicked on a walkable box?
        bool walkable = my_scene->IsBoxWalkable(clickX, clickY);
        if (walkable)
        {
            SetPlayerPath();
        }
        mouseClicked = false;
    }

    //IF PLAYER HASN'T REACHED DESTINATION box,MOVE THE PLAYER TOWARD DESTINATION,
    //if they reach the desination box
    // look up the next node in the player path (until the node has empty children)
    // look up the next desination box by id
    // set the player destination coords as that boxes origins
    // move player to those coords
    // when we reached end of path update player has reachedfinaldest to true;
    my_player.UpdateMovement(deltaTime);





    //Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

}

void Game::SetPlayerPath()
{
    int destBoxId = my_scene->FindCurrentBoxFromCoord(clickX, clickY);

    // Clear any previous path the player had
    my_player.m_pathByBoxId.clear();

    int currentPlayerBox = my_scene->FindCurrentBoxFromCoord(my_player.m_position.x, my_player.m_position.y);

    // Find path between current box and destination box
    my_player.m_pathByBoxId = my_scene->FindPath(currentPlayerBox, destBoxId);
    int length = my_player.m_pathByBoxId.size();
    if (length > 0)
    {
        scene_box* firstbox = my_scene->GetBoxById(my_player.m_pathByBoxId.at(length-1));
        //std::cout << "First box: " << my_player.m_pathByBoxId.at(length-1) << std::endl;
        my_player.m_destination = { firstbox->originX, firstbox->originY};
        my_player.m_playerReachedFinalDestination = false;
    }
    else
    {
        my_player.m_playerReachedFinalDestination = true;
    }

}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21, 21,21 , 255);
    SDL_RenderClear(renderer);
    //ClearColorBuffer(0xFFFFFF00);

    my_scene->Render(renderer);
    my_player.Render(renderer);
//    DrawSceneBoxes();
//    RenderColorBuffer();
    SDL_RenderPresent(renderer);
    ++frameCount;
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