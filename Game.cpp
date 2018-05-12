#include "Game.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include "Sun.h"
#include "Planet.h"
#include "PlayerSnake.h"
#include "AISnake.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::WallCollision(Snake* s)
{
    if(s->GetPosition().x >= m_screenWidth - m_borderSize) // collide with eastBorder
    {
        s->SetAlive(false);
    }
    else if(s->GetPosition().x <= m_borderSize * 5) // collide with westborder
    {
        s->SetAlive(false);
    }
    else if(s->GetPosition().y <= m_borderSize) // collide with northborder
    {
        s->SetAlive(false);
    }
    else if(s->GetPosition().y >= m_screenHeight - m_borderSize) // collide with south border
    {
        s->SetAlive(false);
    }
}

void Game::SnakeCollision()
{
    // loop through each snake
    for (size_t i = 0; i < m_snakes.size(); i++)
    {
        for (size_t j = 0; j < m_snakes.size(); j++)
        {
            if(i != j)
            {
                if (m_snakes[i]->CheckCollision(*m_snakes[j])) // check for collisions
                {
                    m_snakes[i]->SetAlive(false);
                }
            }
        }
    }
}

void Game::CollectableCollision(Sun& s)
{
    for(Collectable& c : m_collectables)
    {
        if(c.IsActive() == false && rand() % 10 == 0 && !m_gameOver) // 1 in 10 chance of spawning
        {
            c.SetGrowAmount(rand() % 2 + 1);
            SetCollectablePosition(c);
            c.SetActive(true);
        }

        //collide with sun, so its not stuck behind it
        if (hypot(s.GetPosition().x - c.GetPosition().x, s.GetPosition().y - c.GetPosition().y) <= (s.GetRadius() + c.GetRadius()))
        {
            SetCollectablePosition(c);
        }

        if(c.IsActive())
            c.DrawCollectable(m_window);

        for(Snake* s : m_snakes)
            s->m_score += c.Collision(s); // returns a score
    }
}

void Game::SetCollectablePosition(Collectable& c)
{
    float x = std::ceil((rand() % (m_screenWidth - (m_borderSize * 5)) + (m_borderSize * 5)) / 20) * 20;
    float y = std::ceil((rand() % (m_screenHeight - m_borderSize) + (m_borderSize)) / 20) * 20;
    c.SetPosition(x, y);
}

void Game::DrawScoreText()
{
    int i = 0;
    for(Snake* s : m_snakes)
    {
        //set and draw score text for each snake
        m_scoreText.setColor(s->GetSnakeColor());
        m_scoreText.setString("Player " + std::to_string(i + 1) + " \n Score " + std::to_string(s->m_score));
        m_scoreText.setPosition(5, m_borderSize + (i * 50));
        //Draw score text
        m_window.draw(m_scoreText);
        i++;
    }

}

void Game::GameOver()
{
    m_alive = 4; //counts how many snakes are still alive
    for(Snake* s : m_snakes)
    {
        if(!s->IsAlive())
        {
            m_alive--;
        }
        if (m_gameOver && s->IsAlive())
        {
            // if last snake alive, its the winner
            m_winner = s;
        }
    }
    if (m_alive <= 1) //if one or no snakes alive, game over
    {
        m_gameOver = true;
    }
    if (m_timeLeft <= 0)
    {
        if(m_alive > 1)
        {
            //chooses winner if more than one alive after time up
            for(Snake* s : m_snakes)
            {
                if(s -> m_score > m_winner-> m_score)
                {
                    m_winner = s;
                    m_winnerScore = s->m_score;
                }
            }
        }
        m_gameOver = true;
    }
}

void Game::Reset()
{
    //resets everything for new game
    for(std::size_t i = 0; i < m_snakes.size(); i++)
        m_snakes.pop_back();
    for (Collectable c : m_collectables)
        c.SetActive(false);

    m_gameOver = false;
    m_hasReset = true;
}

void Game::LoadScores()
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

void Game::SaveScores()
{
    LoadScores();
    for(int i = 0; i < 10; i++)
    {
        //finds high score spot
        if(m_winnerScore > highScores[i].score)
        {
            highScore newScore = { "New", m_winnerScore };
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

void Game::HighScores()
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
        m_gameState = EGameState::eWaitingToStart;

    // Get the window to display its contents
    m_window.display();
}

void Game::MainMenu()
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
                    m_gameState = EGameState::eAtHighScores;
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

void Game::Start()
{
    m_font.loadFromFile("ARCADECLASSIC.TTF"); //font in use

    m_gameState = EGameState::eWaitingToStart;
    while(m_gameState == EGameState::eWaitingToStart)
    {
        if(!m_hasReset) //only resets once
            Reset();

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

        MainMenu();

        //goes to high score screen
        while (m_gameState == EGameState::eAtHighScores)
        {
            HighScores();
        }

        //goes to game
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Run();
            if(m_winnerScore > 0) //saves the need to run SaveScores if there's no scores to be saved
                SaveScores();
        }

        // Get the window to display its contents
        m_window.display();
    }
}

void Game::Run()
{
    m_timer.restart(); //so the timer starts at 90 seconds
    m_hasReset = false; //so it can be reset again once the game ends
    m_gameState = EGameState::eInGame;
    srand(time(NULL));

    // We can still output to the console window
    std::cout << "Starting" << std::endl;

    sf::Clock clock;

    Sun sun(m_window);
    m_planets.push_back(Planet(750, 750, 20, 0.05, 0.05));
    m_planets.push_back(Planet(500, 500, 20, 0.07, 0.07));

    //creates the right amount of player and ai snakes
    for(int i = 0; i < m_amountOfPlayers; i++)
    {
        m_snakes.push_back(new PlayerSnake("Player" + std::to_string(i + 1), m_playerColors[i].color));
    }
    for(int i = 0; i < 4 - m_amountOfPlayers; i++)
    {
        m_snakes.push_back(new AISnake("Player" + std::to_string(i + 1 + m_amountOfPlayers), m_playerColors[i + m_amountOfPlayers].color));
    }

    m_winner = m_snakes[0]; //sets default winner

    // game loop while in game
    while (m_gameState == EGameState::eInGame)
    {
        // Handle any pending SFML events
        // These cover keyboard, mouse,joystick etc.
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    m_gameOver = true; // exit the game when the player presses escape
                    break;

                default:
                    break;
                }
            default:
                break;
            }
        }

        // We must clear the window each time round the loop
        m_window.clear();


        for(Snake* s : m_snakes)
        {
            //have each snake move
            s->SetDirection();
            s->Move();
        }

        // draw to the window and check collisions
        if(!m_gameOver)
        {
            //checks all the collisions
            for(Snake* s : m_snakes)
            {
                s->DrawSnake(m_window);
                s->CheckSelfCollision();
                SnakeCollision();
                WallCollision(s);
                for(Planet& planet : m_planets)  //check each planet
                    s->CheckPlanetCollision(planet);
                s->CheckPlanetCollision(sun);
            }

            CollectableCollision(sun);
        }



        // Needed for time between movement
        while (clock.getElapsedTime().asMilliseconds() < m_gameSpeed);
        clock.restart();

        sun.DrawSun(m_window);

        for(Planet& planet : m_planets) //draw each planet
            planet.DrawPlanet(m_window, sun.GetPosition());

        //Draw north border
        m_window.draw(m_northBorder);
        m_northBorder.setPosition(m_northBorderPos);

        //Draw south border
        m_window.draw(m_southBorder);
        m_southBorder.setPosition(m_southBorderPos);

        //Draw east border
        m_window.draw(m_eastBorder);
        m_eastBorder.setPosition(m_eastBorderPos);

        //Draw west border
        m_window.draw(m_westBorder);
        m_westBorder.setPosition(m_westBorderPos);

        //Draw score text
        DrawScoreText();

        if (!m_gameOver)
        {
            m_timeLeft = m_time - m_timer.getElapsedTime().asSeconds();
        }

        m_timerText.setPosition(10, m_screenHeight - 200);
        m_timerText.setColor(sf::Color::Red);
        m_timerText.setString(std::to_string(m_timeLeft));
        m_window.draw(m_timerText);

        std::cout << std::to_string(m_timeLeft) << std::endl;

        GameOver();

        if(m_gameOver)
        {
            m_gameOverText.setPosition((m_screenWidth / 2) - 240, (m_screenHeight / 2) - 200);
            m_gameOverText.setString("                         GAME OVER \n            Winner  " + m_winner->GetSnakeName() + "! \n \n \n \n \n Press Enter to Return");
            m_window.draw(m_gameOverText);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                for(std::size_t i = 0; i < m_snakes.size(); i++)
                {
                    //delete the snakes
                    delete(m_snakes[i]);
                }
                m_winnerScore = m_winner->m_score;
                m_gameState = EGameState::eAtEndScreen; //return to main menu
            }
        }

        // Get the window to display its contents
        m_window.display();
    }


    std::cout << "Finished" << std::endl;
}
