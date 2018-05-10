#include "Sun.h"
//#include "Snake.h"
#include <cmath>

Sun::Sun(sf::RenderWindow& window)
{
    m_position.x = ((window.getSize().x / 2));
    m_position.y = ((window.getSize().y /2));
    m_circle.setOrigin(GetRadius(), GetRadius());
    m_circle.setPosition(m_position);
}

void Sun::DrawSun(sf::RenderWindow& window)
{

    m_circle.setFillColor(sf::Color(255, 165, 0));
    window.draw(m_circle);
}


//void Sun::Collision(Snake* s)
//{
//    if (hypot(m_sunPosition.x - s->GetPosition().x, m_sunPosition.y - s->GetPosition().y) <= (m_sun.getRadius() + s->m_snakeHead.getRadius()))
//    {
//        s->SetAlive(false);
//    }
//}
