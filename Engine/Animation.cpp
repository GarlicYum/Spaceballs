#include "Animation.h"

// Constructor gets a constant reference to AnimationFrames and the HoldFrameCount
// HoldFrame is the amount of frames I want to go by before changing between 2 pictures in an animation
Animation::Animation(const AnimationFrames& Frames, float HoldFrameCount)
	:
	frames(Frames),
	nHoldFrames(HoldFrameCount / 60.0f)
{}

//This is the function that animates the picture
//framecounter increases every frame
// when framecounter = nHoldFrames then framecounter resets and the curent frame increases
// if the current frame = number of frames  for the animation then current fram resests and the animation is over
void Animation::Advance(float dt)
{
	if ((frameCounter += dt) >= nHoldFrames)
	{
		frameCounter = 0.0f;
		++curFrame;
		if (curFrame == frames.GetFrameCount())
		{
			curFrame = 0;
			isOver = true;
		}
	}
}

void Animation::Reverse(float dt)
{
	if (!isReversed)
	{
		curFrame = frames.GetFrameCount() - 1;
		isReversed = true;
	}
	if ((frameCounter += dt) >= nHoldFrames)
	{
		frameCounter = 0.0f;	
		--curFrame;
		
		if (curFrame == 0)
		{
			isOver = true;
			isReversed = false;
		}
	}
}

bool Animation::AnimEnd() const
{
	return isOver;
}

void Animation::Draw(int X, int Y, Graphics& Gfx)
{
	frames.Draw(X, Y, curFrame, Gfx);
}

void Animation::Reset()
{
	isOver = false;
}

AnimationFrames::AnimationFrames(const std::wstring& Basename, int NumFrames)
{
	for (int i = 0; i < NumFrames; ++i)
	{
		const int j = i + 1;

		std::wstring filename = Basename + std::to_wstring(j) + L".png";
		surfaces.push_back(Surface::FromFile(filename));
	}
}

int AnimationFrames::GetFrameCount() const
{
	return static_cast<int>(surfaces.size());
}

void AnimationFrames::Draw(int X, int Y, int Idx, Graphics& Gfx) const
{
	Gfx.DrawSpriteAlpha(X, Y, surfaces[Idx]);
}

