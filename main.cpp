/*
  Snake ICA start project using SFML
    SFML documentation: http://www.sfml-dev.org/documentation/2.4.2/classes.php
  Windows build
    To build on Windows you need to have the correct version of CodeBlocks
      Download from here: http://www.codeblocks.org/downloads/26
      Must be the download titled "codeblocks-16.01mingw-setup.exe"
*/

#include"Game.h"

int main()
{

    //Game loop
    while (true)
    {
        //new game created each time
        Game snakeGame;

        snakeGame.Start();
    }

    return 0;
}
