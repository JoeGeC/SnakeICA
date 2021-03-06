#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <SFML/Graphics.hpp>

class Collectable
{
    public:
        Collectable();
        void DrawCollectable(sf::RenderWindow &window);
        bool IsActive();
        void SetActive(bool active);
        void SetPosition(float x, float y);
        sf::Vector2f GetPosition();
        sf::Vector2f SetPosition();
        float GetRadius();
        void SetGrowAmount(int i);
        int GetGrowAmount();
        int GetScore();

    protected:

    private:
        int m_score { 10 };
        int m_growAmount { 1 };
        bool m_active {false};
        sf::CircleShape m_colShape{ 8.f };
        sf::Vector2f m_position;
};

#endif // COLLECTABLE_H
