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
#include "GameState.h"
#include "SColor.h"

struct highScore
{
	std::string name;
	int score;
};

class Game
{
    public:
        Game(int screenWidth, int screenHeight);
        ~Game();

        void Start();
        int Run(sf::RenderWindow& window, SColor playerColors[], GameState gameState);

    protected:

    private:
        int m_gameSpeed {50};
        int m_alive { 4 };

        bool m_gameOver { false };
        Snake* m_winner;
        int m_winnerScore { 0 };

        sf::Font m_font;
        sf::Text m_scoreText{ "Score ", m_font, 20 };
        sf::Text m_gameOverText{ "GAME OVER", m_font, 50 };
        sf::Text m_timerText { "Time Left: ", m_font, 120 };

        sf::Clock m_timer;
        int m_timeLeft { 90 };

        void MainMenu();
        int m_amountOfPlayers = 0;

        void DrawScoreText(sf::RenderWindow& window);

        std::vector<Snake*> m_snakes;
        std::vector<Planet> m_planets;
        Collectable m_collectables[5];

        void SetCollectablePosition(Collectable& c);

        void CollectableCollision(Sun& s,sf::RenderWindow& window);
        void WallCollision(Snake* s);
        void SnakeCollision();

        void GameOver();

        int m_screenWidth;
        int m_screenHeight;

        int m_borderSize { 30 };

        //North Border
        sf::RectangleShape m_northBorder{sf::Vector2f(m_screenWidth, m_borderSize)};
        sf::Vector2f m_northBorderPos{ 0, 0 };

        //South border
        sf::RectangleShape m_southBorder{sf::Vector2f(m_screenWidth, m_borderSize)};
        sf::Vector2f m_southBorderPos{ 0, static_cast<float>(m_screenHeight - m_borderSize) };

        //East border
        sf::RectangleShape m_eastBorder{sf::Vector2f(m_borderSize, m_screenHeight)};
        sf::Vector2f m_eastBorderPos{ static_cast<float>(m_screenWidth - m_borderSize), 0 };

        //West border
        sf::RectangleShape m_westBorder{sf::Vector2f(m_borderSize * 5, m_screenHeight)};
        sf::Vector2f m_westBorderPos{ 0, 0 };
};

#endif // GAME_H
