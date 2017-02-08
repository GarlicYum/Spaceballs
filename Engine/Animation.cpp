#include "Animation.h"

Animation::Animation(const AnimationFrames& Frames, int HoldFrameCount)
	:
	frames(Frames),
	nHoldFrames(HoldFrameCount)
{}

void Animation::Advance()
{
	++frameCounter;
	if (frameCounter >= nHoldFrames)
	{
		frameCounter = 0;
		++curFrame;
		if (curFrame == frames.GetFrameCount())
		{
			curFrame = 0;
			isOver = true;
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
	Gfx.DrawSpriteKey(X, Y, surfaces[Idx], surfaces[Idx].GetPixel(0, 0));
}