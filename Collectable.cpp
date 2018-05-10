#include "Collectable.h"
#include "Snake.h"

Collectable::Collectable()
{
    m_colShape.setOrigin(m_colShape.getRadius(), m_colShape.getRadius());
}

void Collectable::DrawCollectable(sf::RenderWindow &window)
{

    window.draw(m_colShape);
    m_colShape.setPosition(m_position);
}

int Collectable::Collision(Snake* s)
{
    if(m_position == s->GetPosition() && s->IsAlive())
    {
        m_active = false;
        s->m_growAmount += m_growAmount;
        return m_score + (s->m_snakeSegments.size() / 2);
    }
    else
    {
        return 0;
    }
}

bool Collectable::IsActive()
{
    return m_active;
}

void Collectable::SetActive(bool active)
{
   m_active = active;
}

sf::Vector2f Collectable::GetPosition()
{
    return m_position;
}

float Collectable::GetRadius()
{
    return m_colShape.getRadius();
}

void Collectable::SetPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}
