#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "SColor.h"

class Menu
{
    public:
        Menu();
        void OpenMenu(GameState gameState);


    protected:

    private:
        void MenuSelection(GameState gameState);
        void HighScores(GameState gameState);
        void LoadScores();
        void SaveScores(int score);

        std::vector<highScore> highScores;

        // Create an instance of the SFML RenderWindow type which represents the display
        // and initialise its size and title text
        sf::RenderWindow m_window{sf::VideoMode(m_screenWidth, m_screenHeight), "C++ Snake ICA : T7051015"};
        int m_screenWidth {1700};
        int m_screenHeight {1000};

        sf::Font m_font;
        sf::Text m_menuText { "Main Menu", m_font, 50 };
        sf::Text m_playerNoText { "Players", m_font, 40 };
        sf::Text m_playerColorText {"Player ", m_font, 40 };
        sf::Text m_highScoreText {"High Scores", m_font, 40 };
        sf::Text m_highScoresText { "Player1", m_font, 40 };
        sf::Text m_newScoreText { "You got a new high score!", m_font, 40 };
        sf::Text m_spaceText { "Press  Space  to  Continue", m_font, 50 };

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

        int m_amountOfPlayers { 1 };
        int m_menuSelection { 0 };
};

#endif // MENU_H
