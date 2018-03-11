/*
  Snake ICA start project using SFML
    SFML documentation: http://www.sfml-dev.org/documentation/2.4.2/classes.php
  Windows build
    To build on Windows you need to have the correct version of CodeBlocks
      Download from here: http://www.codeblocks.org/downloads/26
      Must be the download titled "codeblocks-16.01mingw-setup.exe"
*/

#include <iostream>
#include <cstdlib>
// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>

#include "Snake.h"

int main()
{
    srand(time(NULL));

    // All SFML types and functions are contained in the sf namespace

    // Create an instance of the SFML RenderWindow type which represents the display
    // and initialise its size and title text
    sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Snake ICA : T7051015");

    // Create an instance of the SFML CircleShape and initialise it so radius is 100
    sf::CircleShape shape(100.f);

    // Set the shape's fill colour attribute to Green
    shape.setFillColor(sf::Color::Green);

    // We can still output to the console window
    std::cout << "Starting" << std::endl;

    sf::Vector2f circlePosition(300, 200);

    Snake *playerSnake = new Snake(true);

    // Main loop that continues until we call Close()
    while (window.isOpen())
    {
        // Handle any pending SFML events
        // These cover keyboard, mouse,joystick etc.
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                playerSnake -> SetDirection(event);
                break;
            default:
                break;
            }
        }

        playerSnake -> SnakeMove();

        shape.setPosition(circlePosition);

        // We must clear the window each time round the loop
        window.clear();

        // draw our circle shape to the window
        window.draw(shape);
        playerSnake -> DrawSnake(window);

        // Get the window to display its contents
        window.display();
    }

    std::cout << "Finished" << std::endl;
    return 0;
}
