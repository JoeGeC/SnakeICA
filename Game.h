#ifndef GAME_H
#define GAME_H

// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "Snake.h"
#include "Collectable.h"
#include <string>
#include "Sun.h"

class Game
{
    public:
        Game();
        ~Game();

        void Run();
        void Loop();

    protected:

    private:
        int m_screenWidth {1700};
        int m_screenHeight {1000};
        int m_gameSpeed {50};
        int m_score { 0 };

        bool m_gameOver { false };

        sf::Font m_font;
        sf::Text m_scoreText{ "Score " + std::to_string(m_score), m_font, 20 };
        sf::Text m_gameOverText{ "GAME OVER", m_font, 50 };

        void DrawScoreText();

        std::vector<Snake> m_snakes;
        Collectable m_collectables[5];

        void SetCollectablePosition(Collectable& c);

        void CollectableCollision(Sun& s);
        void WallCollision(Snake& s);
        void SnakeCollision();

        void GameOver();

        // Create an instance of the SFML RenderWindow type which represents the display
        // and initialise its size and title text
        sf::RenderWindow m_window{sf::VideoMode(m_screenWidth, m_screenHeight), "C++ Snake ICA : T7051015"};

        int m_borderSize { 30 };

        //North Border
        sf::RectangleShape m_northBorder{sf::Vector2f(m_screenWidth, m_borderSize)};
        sf::Vector2f m_northBorderPos{ 0, 0 };

        //South border
        sf::RectangleShape m_southBorder{sf::Vector2f(m_screenWidth, m_borderSize)};
        sf::Vector2f m_southBorderPos{ 0, m_screenHeight - m_borderSize };

        //East border
        sf::RectangleShape m_eastBorder{sf::Vector2f(m_borderSize, m_screenHeight)};
        sf::Vector2f m_eastBorderPos{ m_screenWidth - m_borderSize, 0 };

        //West border
        sf::RectangleShape m_westBorder{sf::Vector2f(m_borderSize * 5, m_screenHeight)};
        sf::Vector2f m_westBorderPos{ 0, 0 };
};

#endif // GAME_H
