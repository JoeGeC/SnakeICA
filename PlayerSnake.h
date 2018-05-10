#ifndef PLAYERSNAKE_H
#define PLAYERSNAKE_H

#include "Snake.h"


class PlayerSnake : public Snake
{
    public:
        PlayerSnake(std::string name, sf::Color snakeColor);
        ~PlayerSnake();
        void SetDirection() override;
};

#endif // PLAYERSNAKE_H
