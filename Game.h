#ifndef GAME_H
#define GAME_H

// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "Snake.h"
#include "Collectable.h"

class Game
{
    public:
        Game();
        ~Game();

        void Run();

    protected:

    private:
        int m_screenWidth {800};
        int m_screenHeight {600};
        int m_movementSpeed {100};

        std::vector<Snake> m_snakes;
        Collectable m_collectables[5];

        // Create an instance of the SFML RenderWindow type which represents the display
        // and initialise its size and title text
        sf::RenderWindow m_window{sf::VideoMode(m_screenWidth, m_screenHeight), "C++ Snake ICA : T7051015"};
};

#endif // GAME_H
