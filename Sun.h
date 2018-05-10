#ifndef SUN_H
#define SUN_H
#include <SFML/Graphics.hpp>
//#include "Snake.h"

class Sun
{
    public:
        Sun(sf::RenderWindow& window);
        void DrawSun(sf::RenderWindow& window);
//        void Collision(Snake* s);
        sf::Vector2f GetSunPosition();
        float GetRadius();

    protected:

    private:
        float m_sunSize = 50.f;
        sf::CircleShape m_sun{ m_sunSize };
        sf::Vector2f m_sunPosition;
};

#endif // SUN_H
