#include "Game.h"

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

    // Can check everything has been deleted properly by looking at the heap profiler
    // (due to heap management by C++ the memory usage may not return to 0 as memory
    // gets returned to the heap manager within the program)
    //std::cin.get();

    return 0;
}