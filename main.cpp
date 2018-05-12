/*
  Snake ICA start project using SFML
    SFML documentation: http://www.sfml-dev.org/documentation/2.4.2/classes.php
  Windows build
    To build on Windows you need to have the correct version of CodeBlocks
      Download from here: http://www.codeblocks.org/downloads/26
      Must be the download titled "codeblocks-16.01mingw-setup.exe"
*/

#include"Menu.h"

int main()
{

    //Game loop
    while (true)
    {
        Menu menu;
        GameState gameState;

        menu.OpenMenu(gameState);
    }

    return 0;
}
