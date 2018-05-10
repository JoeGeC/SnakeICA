#include "SolarSystem.h"

SolarSystem::SolarSystem()
{
    //ctor
}

float SolarSystem::GetRadius()
{
    return m_circle.getRadius();
}

sf::Vector2f SolarSystem::GetPosition()
{
    return m_position;
}
