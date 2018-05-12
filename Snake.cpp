#include "Snake.h"
#include <SFML/Graphics.hpp>
#include "Collectable.h"
#include <iostream>

Snake::Snake(std::string name, sf::Color snakeColor) : m_name(name), m_snakeColor(snakeColor)
{
    //sets each snake starting position
    if (name == "Player1")
    {
        m_position.x = 360;
        m_position.y = 200;
    }
    else if (name == "Player2")
    {
        m_position.x = 1500;
        m_position.y = 220;
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
    m_snakeHead.setOrigin(m_snakeHead.getRadius(), m_snakeHead.getRadius()); //set origin to center of shape
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

void Snake::Move()
{
    //move to requested direction
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

    //move
    m_snakeSegments.push_front(m_position);

    if (m_growAmount > 0)
        m_growAmount--;
    else
        m_snakeSegments.pop_back();
}

bool Snake::CheckCollision(const Snake& other) const
{
    //check if colliding with other snakes
    if(IsAlive() && other.IsAlive())
    {
        for (auto& otherSegment : other.m_snakeSegments)
        {
            if (m_snakeSegments.front() == otherSegment)
            {
                return true;
            }
        }
        return false;
    }
    else
        return false;
}

void Snake::CheckSelfCollision()
{
    //checks snake collides with self
    for(size_t i = 1; i < m_snakeSegments.size(); i++)
    {
        std::list<sf::Vector2f>::const_iterator it = m_snakeSegments.begin();
        std::advance(it, i);

        if(m_snakeSegments.front() == *it) //if head collides with body
        {
            m_isAlive = false;
        }
    }
}

void Snake::CheckPlanetCollision(SolarSystem& ss)
{
    //if collides with sun or planets
    for(size_t i = 0; i < m_snakeSegments.size(); i++)
    {
        std::list<sf::Vector2f>::const_iterator it = m_snakeSegments.begin();
        std::advance(it, i);
        if(hypot(ss.GetPosition().x - (*it).x, ss.GetPosition().y - (*it).y) <= (ss.GetRadius() + m_snakeHead.getRadius())) //checks any snake segment collides with sun or planet
        {
            m_snakeSegments.resize(i); //get rid of snake segments from point hit onwards
            if (m_snakeSegments.size() <= 0) //if no snake left, its dead
            {
                SetAlive(false);
            }
            std::cout << "Collision" << std::endl << std::endl;
        }
    }
}

int Snake::CheckCollectableCollision(Collectable& c)
{
    if(m_position == c.GetPosition() && IsAlive())
    {
        c.SetActive(false);
        m_growAmount += c.GetGrowAmount();
        return c.GetScore() + (m_snakeSegments.size() / 2);
    }
    else
    {
        return 0;
    }
}

sf::Vector2f Snake::GetPosition() const
{
    return m_position;
}

sf::Color Snake::GetSnakeColor() const
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

bool Snake::IsAlive() const
{
    return m_isAlive;
}

std::string Snake::GetSnakeName() const
{
    return m_name;
}
