#pragma once

#include <chrono>

class CountdownTimer
{
private:

	std::chrono::steady_clock::time_point startTime;
	int countdownLength;
	int additionalSeconds = 0;

public:

	CountdownTimer(int s);

	void addSeconds(int s);
	double getSeconds();
	void reset();
};