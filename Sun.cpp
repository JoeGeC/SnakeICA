#include "Sun.h"
#include "Snake.h"
#include <cmath>

Sun::Sun(sf::RenderWindow& window)
{
    m_sunPosition.x = ((window.getSize().x / 2));
    m_sunPosition.y = ((window.getSize().y /2));
    m_sun.setOrigin(m_sun.getRadius(), m_sun.getRadius());
    m_sun.setPosition(m_sunPosition);
}

void Sun::DrawSun(sf::RenderWindow& window)
{

    m_sun.setFillColor(sf::Color(255, 165, 0));
    window.draw(m_sun);
}

sf::Vector2f Sun::GetSunPosition()
{
    return m_sunPosition;
}

void Sun::Collision(Snake& s)
{
    if (hypot(m_sunPosition.x - s.GetPosition().x, m_sunPosition.y - s.GetPosition().y) <= (m_sun.getRadius() + s.m_snakeHead.getRadius()))
    {
        s.SetAlive(false);
    }
}

float Sun::GetRadius()
{
    return m_sun.getRadius();
}
