#pragma once

#include "Scene.h"
#include "Utils.h"

// TO DO: SORT ALL THIS OUT, IT'S ONLY TEMPORARY TO VISUALIZE MY PATHFINDING
// REMEMEBER TO ADD SETTING CHECKS FOR DESTINATION ETC TO CHECK IT'S ACTAULLY A VALID DEST ETC ETC.

class Player
{
public:
    vec2 m_position = { 0 , 0 };
    vec2 m_destination = { 0, 0};
    bool m_playerReachedFinalDestination = true;
    std::vector<int> m_pathByBoxId = {};
    Scene* m_scene = nullptr;

    Player(float x, float y)
    {
        m_position = { x, y};
    }

    Player()
    {
        if (m_scene)
        {
            delete m_scene;
        }
    }

    void MovePlayer(int speed, vec2 destinationVec, float deltaTime);

    bool PlayerHasReachedBoxDestination();

    void UpdateMovement(float deltaTime);
};
