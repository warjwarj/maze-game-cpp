#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <iostream>

#include "CountdownTimer.h"

CountdownTimer::CountdownTimer(int s) :
    countdownLength(s)
{
    reset();
}

void CountdownTimer::reset()
{
    additionalSeconds = 0;
    startTime = std::chrono::steady_clock::now();
}

void CountdownTimer::addSeconds(int s)
{
    additionalSeconds += s;
}

double CountdownTimer::getSeconds()
{
    auto endTime = startTime + std::chrono::seconds(countdownLength + additionalSeconds);
    auto diff = endTime - std::chrono::steady_clock::now();
    return std::round(std::chrono::duration<double>(diff).count() * 100) / 100;
}