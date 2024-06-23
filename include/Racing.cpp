#include "Game.h"

#undef main

int main()
{
    Game myGame;

    while (myGame.IsGameRunning())
    {
        myGame.Run(0.1f);
    }

    return 0;
}