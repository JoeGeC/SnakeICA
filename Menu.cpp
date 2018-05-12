#include "Menu.h"
#include <fstream>

Menu::Menu()
{
    //ctor
}

void Menu::OpenMenu(GameState gameState)
{
    m_font.loadFromFile("ARCADECLASSIC.TTF"); //font in use

    while (gameState.GetGameState() == EGameState::eAtMenu)
    {
        // We must clear the window each time round the loop
        m_window.clear();

        m_menuText.setPosition(m_screenWidth / 2 - 150, 50);
        m_window.draw(m_menuText);

        m_playerNoText.setPosition(m_screenWidth / 2 - 200, 150);
        m_playerNoText.setString("Players          " + std::to_string(m_amountOfPlayers));
        m_window.draw(m_playerNoText);

        m_spaceText.setPosition(m_screenWidth / 2 - 300, m_screenHeight - 200);
        m_spaceText.setString("Press Space to Play");
        m_window.draw(m_spaceText);

        m_highScoreText.setPosition(m_screenWidth / 2 - 200, 200);
        m_window.draw(m_highScoreText);

        //draws each player and their colour to the screen
        for(int i = 0; i < 4; i++)
        {
            m_playerColors[i] = m_availableColors[i];
            m_playerColorText.setPosition(m_screenWidth / 2 - 200, 300 + (50 * (i + 1)));
            m_playerColorText.setString("Player" + std::to_string(i + 1) + "    " + m_playerColors[i].name);
            m_playerColorText.setColor(m_playerColors[i].color);
            m_window.draw(m_playerColorText);
        }

        MenuSelection(gameState);

        //goes to high score screen
        while (gameState.GetGameState() == EGameState::eAtHighScores)
        {
            HighScores(gameState);
        }

        //goes to game
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Game newGame(m_screenWidth, m_screenHeight);
            gameState.SetGameState(EGameState::eInGame);
            int score = newGame.Run(m_window, m_playerColors, gameState);
            if (score > 0)
                SaveScores(score);
        }

        // Get the window to display its contents
        m_window.display();
    }
}

void Menu::MenuSelection(GameState gameState)
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
            //chooses which menu element to select
            case sf::Keyboard::Down:
                if(m_menuSelection < 1)
                    m_menuSelection++;
                break;
            case sf::Keyboard::Up:
                if(m_menuSelection > 0)
                    m_menuSelection--;
                break;
            //chooses amount of players when on that option
            case sf::Keyboard::Left:
                if(m_menuSelection == 0 && m_amountOfPlayers > 0)
                    m_amountOfPlayers--;
                //Color selector that currently doesn't work
//                        else if(m_menuSelection == 1 && m_player1ColorSelector > 0)
//                        {
//                            m_player1ColorSelector--;
//                            m_playerColors[0] = m_availableColors[m_player1ColorSelector];
//                        }

                break;
            //chooses amount of players when on that option
            case sf::Keyboard::Right:
                if(m_menuSelection == 0 && m_amountOfPlayers < 2)
                    m_amountOfPlayers++;
            //Color selector that currently doesn't work
//                        else if(m_menuSelection == 1 && m_player1ColorSelector <= 4)
//                        {
//                            m_player1ColorSelector++;
//                            m_playerColors[0] = m_availableColors[m_player1ColorSelector];
//                        }
            //goes to high scores screen
            case sf::Keyboard::Return:
                if(m_menuSelection == 1)
                    gameState.SetGameState(EGameState::eAtHighScores);
            default:
                break;
            }
        default:
            break;
        }
    }

    //changes colours of menu options as you alter between them
    switch(m_menuSelection)
    {
    case(0):
        m_playerNoText.setColor(sf::Color(244, 241, 66));
        m_highScoreText.setColor(sf::Color::White);
        break;
    case(1):
        m_playerNoText.setColor(sf::Color::White);
        m_highScoreText.setColor(sf::Color(244, 241, 66));
        break;
    default:
        break;
    }
}

void Menu::HighScores(GameState gameState)
{

    LoadScores();

    m_window.clear();

    m_highScoreText.setPosition(m_screenWidth / 2 - 120, 50);
    m_window.draw(m_highScoreText);

    //draws each score to the screen
    for(int i = 0; i < 10; i++)
    {
        m_highScoresText.setString(highScores[i].name + "        " + std::to_string(highScores[i].score));
        m_highScoresText.setPosition(m_screenWidth / 2 - 100, 100 + i * 50);
        m_window.draw(m_highScoresText);
    }

    m_spaceText.setPosition(m_screenWidth / 2 - 120, m_screenHeight - 100);
    m_spaceText.setString("Press Esc to return");
    m_window.draw(m_spaceText);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        gameState.SetGameState(EGameState::eAtMenu);

    // Get the window to display its contents
    m_window.display();
}

void Menu::LoadScores()
{
    std::ifstream scoresFile;

    scoresFile.open("saveScores.txt"); //file that scores are kept in

    for (int i = 0; i < 10; i++)
    {
        //copies top 10 scores into highScores vector
        highScores.push_back(highScore());
        scoresFile >> highScores[i].name >> highScores[i].score;
    }

    scoresFile.close();
}

void Menu::SaveScores(int score)
{
    LoadScores();
    for(int i = 0; i < 10; i++)
    {
        //finds high score spot
        if(score > highScores[i].score)
        {
            highScore newScore = { "New", score };
            highScores.insert(highScores.begin() + i, newScore);
            break;
        }
    }

    std::ofstream scoresFile;

    scoresFile.open("saveScores.txt");

    for (int i = 0; i < 10; i++)
    {
        //copies high scores to text file
        scoresFile << highScores[i].name << " " << highScores[i].score << " ";
    }

    scoresFile.close();
}
