#include "Game.h"
#include "Timer.h"

#include <iostream>

#undef main

int main()
{
    Game myGame;
    Timer frameTimer;

    frameTimer.Start(); // First timestep very short but that's fine

    while (myGame.IsGameRunning())
    {
        float deltaTime = frameTimer.Stop();

        frameTimer.Start();

        myGame.Run(deltaTime);

        //std::cout << "FPS: " << 1.0f / deltaTime << std::endl; // Uses vsync (apparently) so FPS should be monitors refresh rate (unless it's running slower)
    }

    return 0;
} 