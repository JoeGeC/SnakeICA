#ifndef SUN_H
#define SUN_H
#include <SFML/Graphics.hpp>
//#include "Snake.h"
#include "SolarSystem.h"

class Sun : public SolarSystem
{
    public:
        Sun(sf::RenderWindow& window);
        void DrawSun(sf::RenderWindow& window);
//        void Collision(Snake* s);

    protected:

    private:
};

#endif // SUN_H
