#include "Game.h"
#include <string>
#include "Sun.h"
#include "Planet.h"
#include "PlayerSnake.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::WallCollision(Snake& s)
{
    if(s.GetPosition().x >= m_screenWidth - m_borderSize) // collide with eastBorder
    {
        s.m_isAlive = false;
    }
    else if(s.GetPosition().x <= m_borderSize * 5) // collide with westborder
    {
        s.m_isAlive = false;
    }
    else if(s.GetPosition().y <= m_borderSize) // collide with northborder
    {
        s.m_isAlive = false;
    }
    else if(s.GetPosition().y >= m_screenHeight - m_borderSize) // collide with south border
    {
        s.m_isAlive = false;
    }
}

void Game::SnakeCollision()
{
    // Check for collisions
    for (size_t i = 0; i < m_snakes.size(); i++)
    {
        for (size_t j = i + 1; j < m_snakes.size(); j++)
        {
            if (m_snakes[i].CheckCollision(m_snakes[j]))
            {
                m_snakes[i].m_isAlive = false;
            }
        }
    }
}

void Game::CollectableCollision()
{
    for(Collectable& c : m_collectables)
    {
        if(c.IsActive() == false && rand() % 10 == 0 && !m_gameOver)
        {
            c.m_position.x = std::ceil((rand() % (m_screenWidth - m_borderSize) + (m_borderSize)) / 20) * 20;
            c.m_position.y = std::ceil((rand() % (m_screenHeight - m_borderSize) + (m_borderSize * 2)) / 20) * 20;
            c.m_active = true;
        }

        if(c.IsActive())
            c.DrawCollectable(m_window);

        for(Snake& s : m_snakes)
            s.m_score += c.Collision(s);
    }
}

void Game::DrawScoreText()
{
    int i = 0;
    for(Snake& s : m_snakes)
    {
        //Draw score text
        m_window.draw(m_scoreText);
        m_scoreText.setColor(s.GetSnakeColor());
        m_scoreText.setString("Player " + std::to_string(i + 1) + " \n Score " + std::to_string(s.m_score));
        m_scoreText.setPosition(5, m_borderSize + (i * 50));
        i++;
    }

}

void Game::GameOver()
{
    bool alive = false;
    for(Snake& s : m_snakes)
    {
        if(s.m_isAlive)
        {
            alive = true;
            break;
        }
    }
    if (!alive)
    {
        m_gameOver = true;
    }
}

void Game::Run()
{
    srand(time(NULL));

    // We can still output to the console window
    std::cout << "Starting" << std::endl;

    sf::Clock clock;

    //SolarSystem solarSystem(m_window);

    Sun sun(m_window);
    Planet planet1(750, 750, 20);
    Planet planet2(500, 500, 10);

    m_snakes.push_back(Snake("Player1", sf::Color(239, 16, 53),  true));
//    m_snakes.push_back(Snake("Player2", sf::Color(66, 134, 244), false));
//    m_snakes.push_back(Snake("Player3", sf::Color(49, 226, 108), false));
//    m_snakes.push_back(Snake("Player4", sf::Color(225, 232, 41), false));

    m_font.loadFromFile("ARCADECLASSIC.TTF");
    m_scoreText.setColor(sf::Color::Red);

    // Main loop that continues until we call Close()
    while (m_window.isOpen())
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
                for (Snake& s : m_snakes)
                    s.SetDirection(event);
                break;
            default:
                break;
            }
        }

        for(Snake& s : m_snakes)
        {
            s.SetAIDirection();
            s.Move();
        }

        // We must clear the window each time round the loop
        m_window.clear();

        // draw to the window
        for(Snake& s : m_snakes)
        {
            s.DrawSnake(m_window);
            s.CheckSelfCollision();
            SnakeCollision();
            WallCollision(s);
            sun.Collision(s);
            planet1.PlanetCollision(s);
            planet2.PlanetCollision(s);
        }

        CollectableCollision();

        // Needed for time between movement
        while (clock.getElapsedTime().asMilliseconds() < m_gameSpeed);
        clock.restart();

        sun.DrawSun(m_window);
        planet1.DrawPlanet(m_window, sun.GetSunPosition(), 0.01, 0.01);
        planet2.DrawPlanet(m_window, sun.GetSunPosition(), 0.02, 0.02);

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

        GameOver();

        if(m_gameOver)
        {
            m_gameOverText.setPosition((m_screenWidth / 2) - 120, (m_screenHeight / 2) - 40);
            m_window.draw(m_gameOverText);
        }

        // Get the window to display its contents
        m_window.display();
    }


    std::cout << "Finished" << std::endl;
}
