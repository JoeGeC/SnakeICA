#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>

enum class Direction
{
    North,
    South,
    East,
    West
};


class Snake
{
    public:
        Snake(bool playerControlled);
        virtual ~Snake();
        void DrawSnake(sf::RenderWindow &window);
        void SetDirection(sf::Event event);
        void SnakeMove();
        sf::CircleShape snakeShape{ 10.f };

    protected:

    private:
        Direction currDirection = Direction::East;
        Direction nextDirection = Direction:: East;
        int movementSpeed { 2 };
        bool playerControlled;

        sf::Vector2f position{30, 30};
};

#endif // SNAKE_H
