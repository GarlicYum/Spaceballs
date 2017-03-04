#include "Timer.h"

Timer::Timer(float time)
	:
	waitTime(time)
{}

bool Timer::Pause(float dt)
{
	return (timer += dt) >= waitTime;
}

void Timer::Reset()
{
	timer = 0.0f;
}

void Timer::SetWaitTime(float newTime)
{
	waitTime = newTime;
}

void Timer::Increment(float dt)
{
	timer += dt;
}

bool Timer::PauseOver()
{
	return timer >= waitTime;
}
