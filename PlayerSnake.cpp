#include "PlayerSnake.h"

PlayerSnake::PlayerSnake(std::string name, sf::Color snakeColor) : Snake(name, snakeColor)
{
    //ctor
}

PlayerSnake::~PlayerSnake()
{
    //dtor
}

EDirection PlayerSnake::SetDirection()
{
    if (m_name == "Player1")
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_currDirection != EDirection::eEast)
            return EDirection::eWest;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_currDirection != EDirection::eWest)
            return EDirection::eEast;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_currDirection != EDirection::eSouth)
            return EDirection::eNorth;
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_currDirection != EDirection::eNorth))
            return EDirection::eSouth;
        else
            return m_reqDirection;
    }
    else if (m_name == "Player2")
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_currDirection != EDirection::eEast)
            return EDirection::eWest;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_currDirection != EDirection::eWest)
            return EDirection::eEast;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_currDirection != EDirection::eSouth)
            return EDirection::eNorth;
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_currDirection != EDirection::eNorth))
            return EDirection::eSouth;
        else
            return m_reqDirection;
    }

}

void PlayerSnake::Update()
{
    m_reqDirection = SetDirection();
}
