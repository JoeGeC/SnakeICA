#include "Snake.h"
#include <SFML/Graphics.hpp>
#include "Collectable.h"

Snake::Snake(std::string name, sf::Color snakeColor, bool isPlayer) : m_name(name), m_snakeColor(snakeColor), m_isPlayer(isPlayer)
{
    if (name == "Player1")
    {
        m_position.x = 360;
        m_position.y = 200;
    }
    else if (name == "Player2")
    {
        m_position.x = 1500;
        m_position.y = 200;
    }
    else if (name == "Player3")
    {
        m_position.x = 360;
        m_position.y = 800;
    }
    else if (name == "Player4")
    {
        m_position.x = 1500;
        m_position.y = 800;
    }

    m_snakeSegments.push_front(m_position);
    m_snakeHead.setOrigin(m_snakeHead.getRadius(), m_snakeHead.getRadius());
    m_snakeHead.setFillColor(snakeColor);
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
    if(m_isPlayer)
    {
        if (m_name == "Player1")
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Left:
                if (m_currDirection != EDirection::eEast)
                    m_reqDirection = EDirection::eWest;
                break;
            case sf::Keyboard::Right:
                if (m_currDirection != EDirection::eWest)
                    m_reqDirection = EDirection::eEast;
                break;
            case sf::Keyboard::Up:
                if (m_currDirection != EDirection::eSouth)
                    m_reqDirection = EDirection::eNorth;
                break;
            case sf::Keyboard::Down:
                if (m_currDirection != EDirection::eNorth)
                    m_reqDirection = EDirection::eSouth;
                break;
            default:
                break;
            }
        }
        else if (m_name == "Player2")
        {
            switch (event.key.code)
            {
            case sf::Keyboard::A:
                if (m_currDirection != EDirection::eEast)
                    m_reqDirection = EDirection::eWest;
                break;
            case sf::Keyboard::D:
                if (m_currDirection != EDirection::eWest)
                    m_reqDirection = EDirection::eEast;
                break;
            case sf::Keyboard::W:
                if (m_currDirection != EDirection::eSouth)
                    m_reqDirection = EDirection::eNorth;
                break;
            case sf::Keyboard::S:
                if (m_currDirection != EDirection::eNorth)
                    m_reqDirection = EDirection::eSouth;
                break;
            default:
                break;
            }
        }
    }
}

void Snake::SetAIDirection()
{

    int randDir = rand() % 4;
    if (!m_isPlayer)
    {
        switch (randDir)
        {
        case(0):
            if(GetPosition().x > 180 && m_currDirection != EDirection::eEast) // collide with west wall
                m_reqDirection = EDirection::eWest;
            break;
        case(1):
            if(GetPosition().y < 940 && m_currDirection != EDirection::eNorth) // collide with south wall
                m_reqDirection = EDirection::eSouth;
            break;
        case(2):
            if(GetPosition().y > 60 && m_currDirection != EDirection::eSouth) // collide with north wall
                m_reqDirection = EDirection::eNorth;
            break;
        case(3):
            if(GetPosition().x < 1640 && m_currDirection != EDirection::eWest) // collide with east wall
                m_reqDirection = EDirection::eEast;
            break;
        }
    }
}

void Snake::Move()
{
    m_currDirection = m_reqDirection;
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
}

bool Snake::CheckCollision(const Snake& other) const
{
    for (auto& otherSegment : other.m_snakeSegments)
    {
        if (m_snakeSegments.front() == otherSegment)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void Snake::CheckSelfCollision()
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

sf::Color Snake::GetSnakeColor()
{
    return m_snakeColor;
}

void Snake::SetAlive(bool alive)
{
    if(alive)
        m_isAlive = true;
    else
        m_isAlive = false;
}

bool Snake::IsAlive()
{
    return m_isAlive;
}
