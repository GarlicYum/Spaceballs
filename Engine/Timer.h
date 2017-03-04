#pragma once

class Timer
{
public:
	Timer(float time);
	bool Pause(float dt);
	void Reset();
	void SetWaitTime(float newTime);
	void Increment(float dt);
	bool PauseOver();

private:
	float timer = 0.0f;
	float waitTime;
};