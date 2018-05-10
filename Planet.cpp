#include "Planet.h"
#include "Sun.h"

Planet::Planet(int planetPosX, int planetPosY, float planetSize)
{
    m_planetPosition.x = planetPosX;
    m_planetPosition.y = planetPosY;
    m_planet.setRadius(planetSize);
    m_planet.setOrigin(m_planet.getRadius(), m_planet.getRadius());
}


void Planet::DrawPlanet(sf::RenderWindow& window, sf::Vector2f sunPosition, float cosVal, float sinVal)
{
    sf::Vector2f temp = m_planetPosition - sunPosition;
    m_planetPosition.x = temp.x * cos(cosVal) - temp.y * sin(sinVal);
    m_planetPosition.y = temp.y * cos(cosVal) + temp.x * sin(sinVal);
    m_planetPosition += sunPosition;
    m_planet.setPosition(m_planetPosition);
    m_planet.setFillColor(sf::Color::Blue);
    window.draw(m_planet);
}

//void Planet::PlanetCollision(Snake* s)
//{
//    if (hypot(m_planetPosition.x - s->GetPosition().x, m_planetPosition.y - s->GetPosition().y) <= (m_planet.getRadius() + s->m_snakeHead.getRadius()))
//    {
//        s->SetAlive(false);
//    }
//}

sf::Vector2f Planet::GetPosition()
{
    return m_planetPosition;
}

float Planet::GetRadius()
{
    return m_planet.getRadius();
}
