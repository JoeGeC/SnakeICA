#include "Snake.h"
#include <SFML/Graphics.hpp>
#include "Collectable.h"
#include <iostream>

Snake::Snake(std::string name, sf::Color snakeColor) : m_name(name), m_snakeColor(snakeColor)
{
    if (name == "Player1")
    {
        m_position.x = 360;
        m_position.y = 200;
    }
    else if (name == "Player2")
    {
        m_position.x = 360;
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

bool Snake::CheckCollision(const Snake* other) const
{
    if(IsAlive() && other->IsAlive())
    {
        for (auto& otherSegment : other->m_snakeSegments)
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
    else
        return false;
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

//void Snake::CheckPlanetCollision(Planet& planet)
//{
//    for(size_t i = 0; i < m_snakeSegments.size(); i++)
//    {
//        std::list<sf::Vector2f>::const_iterator it = m_snakeSegments.begin();
//        std::advance(it, i);
//        if(hypot(planet.GetPosition().x - (*it).x, planet.GetPosition().y - (*it).y) <= (planet.GetRadius() + m_snakeHead.getRadius()))
//        {
//            m_snakeSegments.pop_back();
//            std::cout << "Collision" << std::endl << std::endl;
//        }
//    }
//}

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
