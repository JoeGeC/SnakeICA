#include "AISnake.h"

AISnake::AISnake(std::string name, sf::Color snakeColor) : Snake(name, snakeColor)
{

}

AISnake::~AISnake()
{
    //dtor
}

void AISnake::SetDirection(Collectable c, int screenWidth, int screenHeight)
{
    if (abs(GetPosition().x - c.GetPosition().x - GetPosition().y - c.GetPosition().y) < abs(GetPosition().x - m_target.x - GetPosition().y - m_target.y))
        m_target = c.GetPosition();

    if (m_target.x < m_position.x && m_currDirection != EDirection::eEast)
        m_reqDirection = EDirection::eWest;
    else if (m_target.x > m_position.x && m_currDirection != EDirection::eWest)
        m_reqDirection = EDirection::eEast;
    if (m_target.y < m_position.y && m_currDirection != EDirection::eSouth)
        m_reqDirection = EDirection::eNorth;
    else if (m_target.y > m_position.y && m_currDirection != EDirection::eNorth)
        m_reqDirection = EDirection::eSouth;

    if (m_position.y <= 50 && m_reqDirection == EDirection::eNorth) //if about to hit the north wall
        m_reqDirection = EDirection::eEast;
    if(m_position.x <= 170 && m_reqDirection == EDirection::eWest) //if about to hit the west wall
        m_reqDirection = EDirection::eNorth;
    if(m_position.y >= screenHeight - 50 && m_reqDirection == EDirection::eSouth) //if about to hit the south wall
        m_reqDirection = EDirection::eWest;
    if(m_position.x >= screenWidth - 50 && m_reqDirection == EDirection::eEast) //if about to hit the east wall
        m_reqDirection = EDirection::eSouth;
}
