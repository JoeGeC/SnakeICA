#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <SFML/Graphics.hpp>
class SolarSystem
{
    public:
        SolarSystem();
        float GetRadius();
        sf::Vector2f GetPosition();

    protected:
        float m_circleSize = 45.f;
        sf::CircleShape m_circle{ m_circleSize };
        sf::Vector2f m_position;

    private:
};

#endif // SOLARSYSTEM_H
