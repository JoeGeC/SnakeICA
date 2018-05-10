#include "AISnake.h"

AISnake::AISnake(std::string name, sf::Color snakeColor) : Snake(name, snakeColor)
{
    //ctor
}

AISnake::~AISnake()
{
    //dtor
}

void AISnake::SetDirection()
{
    int randDir = rand() % 4;
    switch (randDir)
    {
    case(0):
        if(m_position.x > 200 && m_currDirection != EDirection::eEast) // collide with west wall
            m_reqDirection = EDirection::eWest;
        break;
    case(1):
        if(m_position.y < 900 && m_currDirection != EDirection::eNorth) // collide with south wall
            m_reqDirection = EDirection::eSouth;
        break;
    case(2):
        if(m_position.y > 100 && m_currDirection != EDirection::eSouth) // collide with north wall
            m_reqDirection = EDirection::eNorth;
        break;
    case(3):
        if(m_position.x < 1600 && m_currDirection != EDirection::eWest) // collide with east wall
            m_reqDirection = EDirection::eEast;
        break;
    }

//    if (c.GetPosition().x < m_position.x && m_currDirection != EDirection::eEast)
//        m_reqDirection = EDirection::eWest;
//    else if (c.GetPosition().x > m_position.x && m_currDirection != EDirection::eWest)
//        m_reqDirection = EDirection::eEast;
//    if (c.GetPosition().y < m_position.y && m_currDirection != EDirection::eSouth)
//        m_reqDirection = EDirection::eNorth;
//    else if (c.GetPosition().y > m_position.y && m_currDirection != EDirection::eNorth)
//        m_reqDirection = EDirection::eSouth;
}
