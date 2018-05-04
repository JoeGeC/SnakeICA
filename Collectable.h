#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <SFML/Graphics.hpp>
#include "Snake.h"
class Collectable
{
    public:
        Collectable();
        virtual ~Collectable();
        void DrawCollectable(sf::RenderWindow &window);
        bool IsActive();
        sf::Vector2f m_position;
        int Collision(Snake& s);
        bool m_active {false};

    protected:

    private:
        int m_score { 10 };
        int m_growAmount { 1 };
        sf::CircleShape m_colShape{ 8.f };
};

#endif // COLLECTABLE_H
