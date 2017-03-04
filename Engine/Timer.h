#pragma once

class Timer
{
public:
	Timer(float time);
	bool Pause(float dt);
	void Reset();
	void SetWaitTime(float newTime);

private:
	float timer = 0.0f;
	float waitTime;
};