#include "Game.h"
#include <string>

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::Collision(Snake& s)
{
    if(s.GetPosition().x >= m_screenWidth - m_borderSize) // collide with eastBorder
    {
        s.m_isAlive = false;
    }
    else if(s.GetPosition().x <= m_borderSize) // collide with westborder
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

    if(s.m_isAlive == false)
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

    m_snakes.push_back(Snake("Player1"));

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
            s.Move();
        }

        // We must clear the window each time round the loop
        m_window.clear();

        // draw to the window
        for(Snake& s : m_snakes)
        {
            s.DrawSnake(m_window);
            Collision(s);
        }

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
                m_score += c.Collision(s);
        }

        // Needed for time between movement
        while (clock.getElapsedTime().asMilliseconds() < m_movementSpeed);
        clock.restart();

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
        m_window.draw(m_scoreText);
        m_scoreText.setString("Score " + std::to_string(m_score));
        m_scoreText.setPosition(m_borderSize, 10);

        if(m_gameOver)
        {
            m_gameOverText.setPosition(300, 250);
            m_window.draw(m_gameOverText);
        }

        // Get the window to display its contents
        m_window.display();
    }


    std::cout << "Finished" << std::endl;
}
