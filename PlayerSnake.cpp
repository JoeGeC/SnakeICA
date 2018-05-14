#include "PlayerSnake.h"

PlayerSnake::PlayerSnake(std::string name, sf::Color snakeColor) : Snake(name, snakeColor)
{
    //ctor
}

PlayerSnake::~PlayerSnake()
{
    //dtor
}

void PlayerSnake::SetDirection(Collectable c, int screenWidth, int screenHeight)
{
    if (m_name == "Player1")
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_currDirection != EDirection::eEast)
            m_reqDirection = EDirection::eWest;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_currDirection != EDirection::eWest)
            m_reqDirection = EDirection::eEast;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_currDirection != EDirection::eSouth)
            m_reqDirection = EDirection::eNorth;
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_currDirection != EDirection::eNorth))
            m_reqDirection = EDirection::eSouth;
    }
    else if (m_name == "Player2")
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_currDirection != EDirection::eEast)
            m_reqDirection = EDirection::eWest;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_currDirection != EDirection::eWest)
            m_reqDirection = EDirection::eEast;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_currDirection != EDirection::eSouth)
            m_reqDirection = EDirection::eNorth;
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_currDirection != EDirection::eNorth))
            m_reqDirection = EDirection::eSouth;
    }
}
