#include <iostream>
#include <chrono>
#include <thread>

#include "CountdownTimer.h"

CountdownTimer::CountdownTimer(int s) :
    countdownLength(s),
    startTime(std::chrono::steady_clock::now())
{
}

void CountdownTimer::addSeconds(int s)
{
    countdownLength += s;
}

int CountdownTimer::getSeconds()
{
    auto secs = std::chrono::seconds(countdownLength);
    auto endTime = startTime + std::chrono::seconds(countdownLength);
    auto diff = endTime - std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(diff).count();
}