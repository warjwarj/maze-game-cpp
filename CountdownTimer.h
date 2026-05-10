#pragma once

#include <chrono>

class CountdownTimer
{
private:

	std::chrono::steady_clock::time_point startTime;
	int countdownLength;

public:

	CountdownTimer(int s);

	void addSeconds(int s);
	int getSeconds();
};