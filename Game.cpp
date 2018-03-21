#include "Game.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::Run()
{
    srand(time(NULL));

    // We can still output to the console window
    std::cout << "Starting" << std::endl;

    sf::Clock clock;


    m_snakes.push_back(Snake("Player1"));
    m_snakes.push_back(Snake("Player2"));

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
        }

        for(Collectable& c : m_collectables)
        {
            if(c.m_active == false && rand() % 10 == 0)
            {
                c.m_position.x = std::ceil((rand() % 800) / 20) * 20;
                c.m_position.y = std::ceil((rand() % 800) / 20) * 20;
                c.m_active = true;
            }
            if(c.m_active)
                c.DrawCollectable(m_window);
        }

        // Get the window to display its contents
        m_window.display();

        while (clock.getElapsedTime().asMilliseconds() < m_movementSpeed);
        clock.restart();
    }

    std::cout << "Finished" << std::endl;
}
