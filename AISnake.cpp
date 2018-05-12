#include "AISnake.h"

AISnake::AISnake(std::string name, sf::Color snakeColor) : Snake(name, snakeColor)
{

}

AISnake::~AISnake()
{
    //dtor
}

void AISnake::SetDirection(Collectable c)
{
    //Needs work

    if (c.GetPosition().x < m_position.x && m_currDirection != EDirection::eEast)
        m_reqDirection = EDirection::eWest;
    else if (c.GetPosition().x > m_position.x && m_currDirection != EDirection::eWest)
        m_reqDirection = EDirection::eEast;
    if (c.GetPosition().y < m_position.y && m_currDirection != EDirection::eSouth)
        m_reqDirection = EDirection::eNorth;
    else if (c.GetPosition().y > m_position.y && m_currDirection != EDirection::eNorth)
        m_reqDirection = EDirection::eSouth;
}
