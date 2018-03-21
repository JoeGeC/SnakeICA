#include "Snake.h"
#include <SFML/Graphics.hpp>

Snake::Snake(std::string name) : m_name(name)
{
    m_position.x = std::ceil((rand() % 400 + 400) / 20) * 20;
    m_position.y = std::ceil((rand() % 200 + 200) / 20) * 20;
}

Snake::~Snake()
{
    //dtor
}

void Snake::DrawSnake(sf::RenderWindow &window)
{
    window.draw(m_snakeHead);
    m_snakeHead.setPosition(m_position);

}

void Snake::SetDirection(sf::Event event)
{
    switch (event.key.code)
    {
    case sf::Keyboard::Left:
        if (m_currDirection != EDirection::eEast)
            m_currDirection = EDirection::eWest;
        break;
    case sf::Keyboard::Right:
        if (m_currDirection != EDirection::eWest)
            m_currDirection = EDirection::eEast;
        break;
    case sf::Keyboard::Up:
        if (m_currDirection != EDirection::eSouth)
            m_currDirection = EDirection::eNorth;
        break;
    case sf::Keyboard::Down:
        if (m_currDirection != EDirection::eNorth)
            m_currDirection = EDirection::eSouth;
        break;
    default:
        break;
    }
}

void Snake::Move()
{
    switch (m_currDirection)
    {
        case EDirection::eEast:
            m_position.x += m_movement;
            break;
        case EDirection::eNorth:
            m_position.y -= m_movement;
            break;
        case EDirection::eWest:
            m_position.x -= m_movement;
            break;
        case EDirection::eSouth:
            m_position.y += m_movement;
            break;
        default:
            break;
    }

    if(m_position.x > 800 - m_movement)
        m_position.x = 0;
    if(m_position.x < 0)
        m_position.x = 800 - m_movement;
    if(m_position.y > 600 - m_movement)
        m_position.y = 0;
    if(m_position.y < 0)
        m_position.y = 600 - m_movement;
}

sf::Vector2f Snake::GetPosition()
{
    return m_position;
}
