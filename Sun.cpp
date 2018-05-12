#include "Sun.h"
//#include "Snake.h"
#include <cmath>

Sun::Sun(sf::RenderWindow& window)
{
    m_position.x = ((window.getSize().x / 2) + 50);
    m_position.y = ((window.getSize().y /2));
    m_circle.setOrigin(GetRadius(), GetRadius()); //sets origin to center of shape
    m_circle.setPosition(m_position);
}

void Sun::DrawSun(sf::RenderWindow& window)
{
    m_circle.setFillColor(sf::Color(255, 165, 0));
    window.draw(m_circle);
}
