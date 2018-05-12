#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "Planet.h"
#include "Collectable.h"

enum class EDirection
{
    eNorth,
    eSouth,
    eEast,
    eWest
};

class Snake
{
    public:
        Snake(std::string name, sf::Color snakeColor);
        virtual ~Snake();
        virtual void SetDirection(Collectable c) = 0;
        void DrawSnake(sf::RenderWindow &window);
        void Move();
        sf::Vector2f GetPosition() const;
        std:: string GetSnakeName() const;
        std::list<sf::Vector2f> m_snakeSegments;
        void SetAlive(bool alive);
        bool IsAlive() const;
        bool CheckCollision(const Snake& other) const;
        void CheckSelfCollision();
        void CheckPlanetCollision(SolarSystem& ss);
        int CheckCollectableCollision(Collectable& c);
        sf::Color GetSnakeColor() const;
        sf::CircleShape m_snakeHead{ 10.f };
        int m_growAmount { 0 };
        int m_score { 0 };


    protected:
        EDirection m_currDirection = EDirection::eSouth;
        EDirection m_reqDirection = EDirection::eSouth;
        sf::Vector2f m_position;
        std::string m_name;

    private:
        int m_movement = m_snakeHead.getRadius() * 2;
        sf::Color m_snakeColor;

        bool m_isAlive { true };
};

#endif // SNAKE_H
