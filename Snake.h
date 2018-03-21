#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <string>

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
        Snake(std::string name);
        virtual ~Snake();
        void DrawSnake(sf::RenderWindow &window);
        void SetDirection(sf::Event event);
        void Move();
        sf::Vector2f GetPosition();
        sf::CircleShape m_snakeHead{ 10.f };

    protected:

    private:
        EDirection m_currDirection = EDirection::eEast;
        int m_movement = m_snakeHead.getRadius() * 2;
        bool m_playerControlled;
        std::string m_name;

        sf::Vector2f m_position;
};

#endif // SNAKE_H
