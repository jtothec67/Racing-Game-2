#include "Game.h"
#include "Timer.h"

#include <iostream>

#undef main

int main()
{
    {
        Game myGame;

        while (myGame.IsGameRunning())
        {
            myGame.Run();
        }
    }

    // Can check everything has been deleted properly by looking at memory usage (should be 45mb)
    //std::cin.get();

    return 0;
}