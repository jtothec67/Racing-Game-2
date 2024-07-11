#include "Timer.h"

void Timer::Start()
{
	mStart = std::chrono::steady_clock::now();
	mEnd = mStart;
}

float Timer::Stop()
{
	mEnd = std::chrono::steady_clock::now();

	return GetTime();
}

float Timer::GetTime()
{
	std::chrono::duration<float> duration = mEnd - mStart;

	return duration.count();
}