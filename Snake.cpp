#include "Snake.h"
#include <SFML/Graphics.hpp>

Snake::Snake(std::string name) : m_name(name)
{
    m_position.x = std::ceil((rand() % 400 + 80) / 20) * 20;
    m_position.y = std::ceil((rand() % 300 + 80) / 20) * 20;
    m_snakeSegments.push_front(m_position);
}

Snake::~Snake()
{
    //dtor
}

void Snake::DrawSnake(sf::RenderWindow &window)
{
    for(auto& s : m_snakeSegments)
    {
        if(m_isAlive)
        {
            m_snakeHead.setPosition(s);
            window.draw(m_snakeHead);
        }
    }
}

void Snake::SetDirection(sf::Event event)
{
    if (m_name == "Player1")
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
    if (m_name == "Player2")
    {
        switch (event.key.code)
        {
        case sf::Keyboard::A:
            if (m_currDirection != EDirection::eEast)
                m_currDirection = EDirection::eWest;
            break;
        case sf::Keyboard::D:
            if (m_currDirection != EDirection::eWest)
                m_currDirection = EDirection::eEast;
            break;
        case sf::Keyboard::W:
            if (m_currDirection != EDirection::eSouth)
                m_currDirection = EDirection::eNorth;
            break;
        case sf::Keyboard::S:
            if (m_currDirection != EDirection::eNorth)
                m_currDirection = EDirection::eSouth;
            break;
        default:
            break;
        }
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

    m_snakeSegments.push_front(m_position);

    if (m_growAmount > 0)
        m_growAmount--;
    else
        m_snakeSegments.pop_back();

    if(m_position.x > 800 - m_movement)
        m_position.x = 0;
    if(m_position.x < 0)
        m_position.x = 800 - m_movement;
    if(m_position.y > 600 - m_movement)
        m_position.y = 0;
    if(m_position.y < 0)
        m_position.y = 600 - m_movement;
}

bool Snake::CheckCollision(const Snake& other) const
{
    for (auto& otherSegment : other.m_snakeSegments)
    {
        if (m_snakeSegments.front() == otherSegment)
        {
            return true;
        }
    }
}

bool Snake::CheckSelfCollision()
{
    for(size_t i = 1; i < m_snakeSegments.size(); i++)
    {
        std::list<sf::Vector2f>::const_iterator it = m_snakeSegments.begin();
        std::advance(it, i);

        if(m_snakeSegments.front() == *it)
        {
            m_isAlive = false;
        }
    }
}

sf::Vector2f Snake::GetPosition()
{
    return m_position;
}
