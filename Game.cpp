#include "Game.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
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
    // Check for collisions
    for (size_t i = 0; i < m_snakes.size(); i++)
    {
        for (size_t j = 0; j < m_snakes.size(); j++)
        {
            if (m_snakes[i]->CheckCollision(m_snakes[j]) && i != j)
            {
                m_snakes[i]->SetAlive(false);
            }
        }
    }
}

void Game::CollectableCollision(Sun& s)
{
    for(Collectable& c : m_collectables)
    {
        if(c.IsActive() == false && rand() % 10 == 0 && !m_gameOver)
        {
            SetCollectablePosition(c);
            c.SetActive(true);
        }

        if (hypot(s.GetPosition().x - c.GetPosition().x, s.GetPosition().y - c.GetPosition().y) <= (s.GetRadius() + c.GetRadius()))
        {
            SetCollectablePosition(c);
        }

        if(c.IsActive())
            c.DrawCollectable(m_window);

        for(Snake* s : m_snakes)
            s->m_score += c.Collision(s);
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
    m_alive = 4;
    for(Snake* s : m_snakes)
    {
        if(!s->IsAlive())
        {
            m_alive--;
        }
        if (m_gameOver && s->IsAlive())
        {
            m_winner = s;
        }
    }
    if (m_alive <= 1)
    {
        m_gameOver = true;
    }
    if (m_timeLeft <= 0)
    {
        if(m_alive > 1)
        {
            for(Snake* s : m_snakes)
            {
                if(s -> m_score > m_winner-> m_score)
                    m_winner = s;
            }
        }
        m_gameOver = true;
    }
}

void Game::Reset()
{
    for (Snake* s : m_snakes)
        m_snakes.pop_back();
    for (Collectable c : m_collectables)
        c.SetActive(false);

    m_gameOver = false;
    m_hasReset = true;
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
                    //in case more menu options are added
                    case sf::Keyboard::Down:
                        if(m_menuSelection < 0)
                            m_menuSelection++;
                        break;
                    case sf::Keyboard::Up:
                        if(m_menuSelection > 0)
                            m_menuSelection--;
                        break;
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
                    case sf::Keyboard::Right:
                        if(m_menuSelection == 0 && m_amountOfPlayers < 2)
                            m_amountOfPlayers++;
//                        else if(m_menuSelection == 1 && m_player1ColorSelector <= 4)
//                        {
//                            m_player1ColorSelector++;
//                            m_playerColors[0] = m_availableColors[m_player1ColorSelector];
//                        }
                    default:
                        break;
                }
            default:
                break;
        }
    }

    switch(m_menuSelection)
    {
        case(0):
            m_playerNoText.setColor(sf::Color(244, 241, 66));
            break;
        case(1):
            m_playerNoText.setColor(sf::Color::White);
            break;
        default:
            break;
    }
}

void Game::Start()
{
    m_font.loadFromFile("ARCADECLASSIC.TTF");

    m_gameState = EGameState::eWaitingToStart;
    while(m_gameState == EGameState::eWaitingToStart)
    {
        if(!m_hasReset)
            Reset();

        // We must clear the window each time round the loop
        m_window.clear();

        m_menuText.setPosition(m_screenWidth / 2 - 150, 50);
        m_window.draw(m_menuText);

        m_playerNoText.setPosition(m_screenWidth / 2 - 200, 150);
        m_playerNoText.setString("Players         " + std::to_string(m_amountOfPlayers));
        m_window.draw(m_playerNoText);

        m_spaceText.setPosition(m_screenWidth / 2 - 300, m_screenHeight - 200);
        m_window.draw(m_spaceText);


        for(int i = 0; i < 4; i++)
        {
            m_playerColors[i] = m_availableColors[i];
            m_playerColorText.setPosition(m_screenWidth / 2 - 200, 200 + (50 * (i + 1)));
            m_playerColorText.setString("Player" + std::to_string(i + 1) + "    " + m_playerColors[i].name);
            m_playerColorText.setColor(m_playerColors[i].color);
            m_window.draw(m_playerColorText);
        }

        MainMenu();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Run();
        }

        // Get the window to display its contents
        m_window.display();
    }
}

void Game::Run()
{
    m_timer.restart();
    m_hasReset = false;
    m_gameState = EGameState::eInGame;
    srand(time(NULL));

    // We can still output to the console window
    std::cout << "Starting" << std::endl;

    sf::Clock clock;

    Sun sun(m_window);

    Planet planet1(750, 750, 20);
    Planet planet2(500, 500, 15);

    for(int i = 0; i < m_amountOfPlayers; i++)
    {
        m_snakes.push_back(new PlayerSnake("Player" + std::to_string(i + 1), m_playerColors[i].color));
    }
    for(int i = 0; i < 4 - m_amountOfPlayers; i++)
    {
        m_snakes.push_back(new AISnake("Player" + std::to_string(i + 1 + m_amountOfPlayers), m_playerColors[i + m_amountOfPlayers].color));
    }

    m_winner = m_snakes[0];

    // Main loop that continues until we call Close()
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
                    case sf::Keyboard::Escape:
                        m_gameOver = true;
                        break;
            default:
                break;
            }
        }

        // We must clear the window each time round the loop
        m_window.clear();


        for(Snake* s : m_snakes)
        {
            s->SetDirection();
            s->Move();
        }

        // draw to the window and check collisions
        if(!m_gameOver)
        {
            for(Snake* s : m_snakes)
            {
                s->DrawSnake(m_window);
                s->CheckSelfCollision();
                SnakeCollision();
                WallCollision(s);
                s->CheckPlanetCollision(planet1);
                s->CheckPlanetCollision(planet2);
                s->CheckPlanetCollision(sun);
            }

            CollectableCollision(sun);
        }



        // Needed for time between movement
        while (clock.getElapsedTime().asMilliseconds() < m_gameSpeed);
        clock.restart();

        sun.DrawSun(m_window);
        planet1.DrawPlanet(m_window, sun.GetPosition(), 0.01, 0.01);
        planet2.DrawPlanet(m_window, sun.GetPosition(), 0.02, 0.02);

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
            m_timeLeft = 90 - m_timer.getElapsedTime().asSeconds();
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
                m_gameState = EGameState::eAtEndScreen;
        }

        // Get the window to display its contents
        m_window.display();
    }


    std::cout << "Finished" << std::endl;
}
