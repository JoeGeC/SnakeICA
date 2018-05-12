#include "Planet.h"
#include "Sun.h"

Planet::Planet(int planetPosX, int planetPosY, float planetSize, float cosVal, float sinVal) : m_cosVal(cosVal), m_sinVal(sinVal)
{
    m_position.x = planetPosX;
    m_position.y = planetPosY;
    m_circle.setRadius(planetSize);
    m_circle.setOrigin(GetRadius(), GetRadius());
}


void Planet::DrawPlanet(sf::RenderWindow& window, sf::Vector2f sunPosition)
{
    //sets position to rotate around sun
    sf::Vector2f temp = m_position - sunPosition;
    m_position.x = temp.x * cos(m_cosVal) - temp.y * sin(m_sinVal);
    m_position.y = temp.y * cos(m_cosVal) + temp.x * sin(m_sinVal);
    m_position += sunPosition;
    m_circle.setPosition(m_position);
    m_circle.setFillColor(sf::Color::Blue);
    window.draw(m_circle);
}
