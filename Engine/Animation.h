#pragma once
#include "Graphics.h"
#include "Surface.h"
#include <string>
#include <vector>

class AnimationFrames
{
public:
	AnimationFrames(const std::wstring& Basename, int NumFrames);
	int GetFrameCount() const;
	void Draw(int X, int Y, int Idx, Graphics& Gfx) const;

private:
	std::vector<Surface> surfaces;
};

class Animation
{
public:
	Animation(const AnimationFrames& Frames, float HoldFrameCount);
	void Advance(float dt);
	void Reverse(float dt);
	bool AnimEnd() const;
	void Draw(int X, int Y, Graphics& Gfx);
	void Reset();

private:
	const AnimationFrames& frames;
	int surfCount = 0;
	float nHoldFrames = 0.0f;
	int curFrame = 0;
	float frameCounter = 0.0f;
	bool isOver = false;
	bool isReversed = false;
};