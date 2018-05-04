#include "Collectable.h"
#include "Snake.h"

Collectable::Collectable()
{
    m_colShape.setOrigin(m_colShape.getRadius(), m_colShape.getRadius());
}

Collectable::~Collectable()
{
    //dtor
}

void Collectable::DrawCollectable(sf::RenderWindow &window)
{

    window.draw(m_colShape);
    m_colShape.setPosition(m_position);
}

bool Collectable::IsActive()
{
    return m_active;
}

int Collectable::Collision(Snake& s)
{
    if(m_position == s.GetPosition())
    {
        m_active = false;
        s.m_growAmount += m_growAmount;
        return m_score;
    }
    else
    {
        return 0;
    }
}
