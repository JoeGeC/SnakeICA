#ifndef PLANET_H
#define PLANET_H

#include "Sun.h"
#include <SFML/Graphics.hpp>

class Planet
{
    public:
        Planet(int planetPosX, int planetPosY, float planetSize);
        void DrawPlanet(sf::RenderWindow& window, sf::Vector2f sunPosition, float cosVal, float sinVal);
        void PlanetCollision(Snake& s);

    protected:

    private:
        sf::CircleShape m_planet;
        sf::Vector2f m_planetPosition;
};

#endif // PLANET_H
