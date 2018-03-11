#include "Snake.h"
#include <SFML/Graphics.hpp>

Snake::Snake(bool playerControlled)
{

}

Snake::~Snake()
{
    //dtor
}

void Snake::DrawSnake(sf::RenderWindow &window)
{
    window.draw(snakeShape);
    snakeShape.setPosition(position);

}

void Snake::SetDirection(sf::Event event)
{
    switch (event.key.code)
    {
    case sf::Keyboard::Left:
        if (currDirection != Direction::East)
            nextDirection = Direction::West;
        break;
    case sf::Keyboard::Right:
        if (currDirection != Direction::West)
            nextDirection = Direction::East;
        break;
    case sf::Keyboard::Up:
        if (currDirection != Direction::South)
            nextDirection = Direction::North;
        break;
    case sf::Keyboard::Down:
        if (currDirection != Direction::North)
            nextDirection = Direction::South;
        break;
    default:
        break;
    }
}

void Snake::SnakeMove()
{
    int x = snakeShape.getPosition().x;
    int y = snakeShape.getPosition().y;
    if ((currDirection == Direction::East || currDirection == Direction::West) && x % 10 == 0)
        currDirection = nextDirection;
    else if ((currDirection == Direction::North || currDirection == Direction::South) && y % 10 == 0)
        currDirection = nextDirection;
    switch (currDirection)
    {
        case Direction::East:
            position.x += movementSpeed;
            break;
        case Direction::North:
            position.y -= movementSpeed;
            break;
        case Direction::West:
            position.x -= movementSpeed;
            break;
        case Direction::South:
            position.y += movementSpeed;
            break;
        default:
            break;
    }
}
