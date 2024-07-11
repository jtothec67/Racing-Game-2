#pragma once

#include <chrono>

class Timer
{
public:
	void Start();
	float Stop();

private:
	float GetTime();

	std::chrono::steady_clock::time_point mStart;
	std::chrono::steady_clock::time_point mEnd;
};