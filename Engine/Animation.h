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
	Animation(const AnimationFrames& Frames, int HoldFrameCount);
	void Advance();
	bool AnimEnd() const;
	void Draw(int X, int Y, Graphics& Gfx);
	void Reset();

private:
	const AnimationFrames& frames;
	int surfCount = 0;
	int nHoldFrames = 0;
	int curFrame = 0;
	int frameCounter = 0;
	bool isOver = false;
};