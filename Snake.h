#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <list>

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
        Snake(std::string name, sf::Color snakeColor, bool isPlayer);
        virtual ~Snake();
        void DrawSnake(sf::RenderWindow &window);
        void SetDirection(sf::Event event);
        void Move();
        sf::Vector2f GetPosition();
        std::list<sf::Vector2f> m_snakeSegments;
        sf::CircleShape m_snakeHead{ 10.f };
        int m_growAmount { 0 };
        int m_score { 0 };
        bool m_isAlive { true };
        bool CheckCollision(const Snake& other) const;
        void CheckSelfCollision();
        sf::Color GetSnakeColor();
        void SetAIDirection();

    protected:

    private:
        EDirection m_currDirection = EDirection::eEast;
        EDirection m_reqDirection = EDirection::eEast;
        int m_movement = m_snakeHead.getRadius() * 2;
        bool m_playerControlled;
        std::string m_name;
        sf::Color m_snakeColor;

        sf::Vector2f m_position;
        bool m_isPlayer = true;
};

#endif // SNAKE_H
