#ifndef AISNAKE_H
#define AISNAKE_H

#include "Snake.h"
#include "Collectable.h"


class AISnake : public Snake
{
    public:
        AISnake(std::string name, sf::Color snakeColor);
        virtual ~AISnake();
        void SetDirection(Collectable c) override;

    private:
};

#endif // AISNAKE_H
