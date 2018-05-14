#ifndef AISNAKE_H
#define AISNAKE_H

#include "Snake.h"
#include "Collectable.h"


class AISnake : public Snake
{
    public:
        AISnake(std::string name, sf::Color snakeColor);
        virtual ~AISnake();
        void SetDirection(Collectable c,int screenWidth, int screenHeight) override;

    private:
        sf::Vector2f m_target = { 9999, 9999 };
};

#endif // AISNAKE_H
