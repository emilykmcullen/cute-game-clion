//#include "Player.h"
//#include <math.h>
//
//void Player::MovePlayer(int speed, vec2 destinationVec, float deltaTime)
//{
//    vec2 moveDirection = { destinationVec.x - m_position.x, destinationVec.y - m_position.y};
//    float lengthOfVec = sqrt((moveDirection.x)*(moveDirection.x) + (moveDirection.y)*(moveDirection.y));
//
//    vec2 normalizedMoveDir = { (moveDirection.x)/lengthOfVec, (moveDirection.y)/lengthOfVec};
//    m_position = { m_position.x += (normalizedMoveDir.x * speed * deltaTime), m_position.y += (normalizedMoveDir.y * speed * deltaTime) };
//    //std::cout << "PLAYER POSITION: " << m_position.x << ", " << m_position.y << std::endl;
//
//}
//
//bool Player::PlayerHasReachedBoxDestination()
//{
//    if (m_position.x <= m_destination.x + 2  && m_position.x >= m_destination.x - 2 && m_position.y <= m_destination.y + 2 && m_position.y >= m_destination.y - 2)
//    {
//        //If we are near enough to dest, clamp to dest
//        m_position.x = m_destination.x;
//        m_position.y = m_destination.y;
//        return true;
//    }
//    return false;
//}
//
//void Player::UpdateMovement(float deltaTime)
//{
//    if (!m_playerReachedFinalDestination)
//    {
//        int length = m_pathByBoxId.size();
//        if (!PlayerHasReachedBoxDestination())
//        {
//            MovePlayer(200, m_destination, deltaTime);
//        }
//        else if (length == 1)
//        {
//            m_playerReachedFinalDestination = true;
//            std::cout << "PLAYER REACHED FINAL DESTINATION" << std::endl;
//        }
//        else
//        {
//            // It hasn't reached the final destination, but it has reached the next box in it's path
//            // So we need to advance to the next box in the path
//            m_pathByBoxId.pop_back();
//            int length = m_pathByBoxId.size();
//            scene_box* nextbox = m_scene->GetBoxById(m_pathByBoxId.at(length-1));
//            //std::cout << "SWITCHING TO NEXT BOX: " << my_player.m_pathByBoxId.at(length-1) <<  std::endl;
//            m_destination = { nextbox->originX, nextbox->originY };
//            //std::cout << my_player.m_destination.x << ", " << my_player.m_destination.y << std::endl;
//            MovePlayer(200, m_destination, deltaTime);
//        }
//
//        //Move the position of the rectangle position where we render the sprite
//        spriteComponent.destinationRectangle.x = m_position.x;
//        spriteComponent.destinationRectangle.y = m_position.y;
//
//    }
//}
//
//
//void Player::Render(SDL_Renderer* renderer)
//{
//    spriteComponent.Render(renderer);
//}


