#ifndef PLANET_H
#define PLANET_H

#include "Sun.h"
#include "SolarSystem.h"
#include <SFML/Graphics.hpp>

class Planet : public SolarSystem
{
    public:
        Planet(int planetPosX, int planetPosY, float planetSize, float cosVal, float sinVal);
        void DrawPlanet(sf::RenderWindow& window, sf::Vector2f sunPosition);

    protected:

    private:
        float m_sinVal { 0.1 };
        float m_cosVal { 0.1 };
};

#endif // PLANET_H
