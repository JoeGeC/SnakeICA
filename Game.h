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

enum class EGameState
{
    eWaitingToStart,
    eInGame,
    eAtEndScreen,
    eAtHighScores,
};

struct SColor
{
    sf::Color color;
    std::string name;
};

struct highScore
{
	std::string name;
	int score;
};

class Game
{
    public:
        Game();
        ~Game();

        void Start();

    protected:

    private:
        EGameState m_gameState { EGameState::eWaitingToStart };

        int m_screenWidth {1700};
        int m_screenHeight {1000};
        int m_gameSpeed {50};
        int m_alive { 4 };

        std::vector<highScore> highScores;

        bool m_gameOver { false };
        Snake* m_winner;
        int m_winnerScore { 0 };

        sf::Font m_font;
        sf::Text m_scoreText{ "Score ", m_font, 20 };
        sf::Text m_gameOverText{ "GAME OVER", m_font, 50 };
        sf::Text m_timerText { "Time Left: ", m_font, 120 };
        sf::Text m_menuText { "Main Menu", m_font, 50 };
        sf::Text m_spaceText { "Press  Space  to  Continue", m_font, 50 };
        sf::Text m_playerNoText { "Players", m_font, 40 };
        sf::Text m_timeSelectText { "Time ", m_font, 40 };
        sf::Text m_playerColorText {"Player ", m_font, 40 };
        sf::Text m_highScoreText {"High Scores", m_font, 40 };
        sf::Text m_highScoresText { "Player1", m_font, 40 };
        sf::Text m_newScoreText { "You got a new high score!", m_font, 40 };

        sf::Clock m_timer;
        int m_timeLeft { 90 };
        int m_time { 90 };

        void Run();
        void MainMenu();
        int m_menuSelection = 0;
        int m_amountOfPlayers = 0;

        SColor red = { sf::Color(239, 16, 53), "Red" };
        SColor blue = { sf::Color(66, 134, 244), "Blue" };
        SColor green = { sf::Color(49, 226, 108), "Green" };
        SColor yellow = { sf::Color(225, 232, 41), "Yellow" };
        SColor m_availableColors[4]{ red, blue, green, yellow };
        SColor m_playerColors[4]{ red, blue, green, yellow };
//        int m_player1ColorSelector = 0;
//        sf::Color m_player1Color = sf::Color(239, 16, 53);
//        sf::Color m_player2Color = sf::Color(66, 134, 244);
//        sf::Color m_player3Color = sf::Color(49, 226, 108);
//        sf::Color m_player4Color = sf::Color(225, 232, 41);

        void DrawScoreText();

        std::vector<Snake*> m_snakes;
        std::vector<Planet> m_planets;
        Collectable m_collectables[5];

        void SetCollectablePosition(Collectable& c);

        void CollectableCollision(Sun& s);
        void WallCollision(Snake* s);
        void SnakeCollision();

        void GameOver();
        void Reset();
        bool m_hasReset { false };

        void HighScores();
        void LoadScores();
        void SaveScores();

        // Create an instance of the SFML RenderWindow type which represents the display
        // and initialise its size and title text
        sf::RenderWindow m_window{sf::VideoMode(m_screenWidth, m_screenHeight), "C++ Snake ICA : T7051015"};

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
