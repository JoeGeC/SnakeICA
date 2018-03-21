#include "Collectable.h"
#include "Snake.h"

Collectable::Collectable()
{

}

Collectable::~Collectable()
{
    //dtor
}

void Collectable::DrawCollectable(sf::RenderWindow &window)
{

    window.draw(m_colShape);
    m_colShape.setPosition(m_position);
    m_colShape.setFillColor(sf::Color::Green);

}

bool Collectable::IsActive()
{
    return m_active;
}

void Collectable::Collision(Snake s)
{
    if(m_position == s.GetPosition())
    {
        m_active = false;
    }
}
