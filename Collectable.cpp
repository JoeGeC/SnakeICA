#include "Collectable.h"

Collectable::Collectable()
{
    m_colShape.setOrigin(m_colShape.getRadius(), m_colShape.getRadius()); //sets origin to center of shape
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

void Collectable::SetGrowAmount(int i)
{
    m_growAmount = i;
}

int Collectable::GetGrowAmount()
{
    return m_growAmount;
}

int Collectable::GetScore()
{
    return m_score;
}
