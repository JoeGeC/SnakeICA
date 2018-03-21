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
        bool m_active {false};
        sf::Vector2f m_position;
        void Collision(Snake s);

    protected:

    private:
        int m_score;
        sf::CircleShape m_colShape{ 10.f };



};

#endif // COLLECTABLE_H
