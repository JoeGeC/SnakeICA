#ifndef AISNAKE_H
#define AISNAKE_H

#include "Snake.h"


class AISnake : public Snake
{
    public:
        AISnake(std::string name, sf::Color snakeColor);
        virtual ~AISnake();
        void Update() override;
        EDirection SetDirection();
};

#endif // AISNAKE_H
