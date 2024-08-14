#pragma once

#include <chrono>

class Timer
{
public:
    void Start();
    float Stop(); // Get time passed and stop the timer
    float GetElapsedTime(); // Get time passed without stopping the timer

    bool IsRunning() { return mRunning; }

private:
    std::chrono::steady_clock::time_point mStart;
    std::chrono::steady_clock::time_point mEnd;
    std::chrono::steady_clock::time_point mTempTimeStamp;

    bool mRunning = false;
};