#include "AISnake.h"

AISnake::AISnake(std::string name, sf::Color snakeColor) : Snake(name, snakeColor)
{
    //ctor
}

AISnake::~AISnake()
{
    //dtor
}

EDirection AISnake::SetDirection()
{
    int randDir = rand() % 4;
    switch (randDir)
    {
    case(0):
        if(m_position.x > 180 && m_currDirection != EDirection::eEast) // collide with west wall
            return EDirection::eWest;
        break;
    case(1):
        if(m_position.y < 940 && m_currDirection != EDirection::eNorth) // collide with south wall
            return EDirection::eSouth;
        break;
    case(2):
        if(m_position.y > 60 && m_currDirection != EDirection::eSouth) // collide with north wall
            return EDirection::eNorth;
        break;
    case(3):
        if(m_position.x < 1640 && m_currDirection != EDirection::eWest) // collide with east wall
            return EDirection::eEast;
        break;
    }

}

void AISnake::Update()
{
    m_reqDirection = SetDirection();
}
