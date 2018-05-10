#include "Planet.h"
#include "Sun.h"

Planet::Planet(int planetPosX, int planetPosY, float planetSize)
{
    m_position.x = planetPosX;
    m_position.y = planetPosY;
    m_circle.setRadius(planetSize);
    m_circle.setOrigin(GetRadius(), GetRadius());
}


void Planet::DrawPlanet(sf::RenderWindow& window, sf::Vector2f sunPosition, float cosVal, float sinVal)
{
    sf::Vector2f temp = m_position - sunPosition;
    m_position.x = temp.x * cos(cosVal) - temp.y * sin(sinVal);
    m_position.y = temp.y * cos(cosVal) + temp.x * sin(sinVal);
    m_position += sunPosition;
    m_circle.setPosition(m_position);
    m_circle.setFillColor(sf::Color::Blue);
    window.draw(m_circle);
}

//void Planet::PlanetCollision(Snake* s)
//{
//    if (hypot(m_planetPosition.x - s->GetPosition().x, m_planetPosition.y - s->GetPosition().y) <= (m_planet.getRadius() + s->m_snakeHead.getRadius()))
//    {
//        s->SetAlive(false);
//    }
//}
