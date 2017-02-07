#include "Animation.h"

Animation::Animation()
{
	std::wstring filename;
	for (int i = 0; i < nExploFrames; ++i)
	{
		const int j = i + 1;

		filename = L"mineExplo\\" + std::to_wstring(j) + L".png";

		explo[i] = Surface::FromFile(filename);
	}
	for (int i = 0; i < nShipFrames; ++i)
	{
		const int j = i + 1;

		filename = L"shipDestroyed\\" + std::to_wstring(j) + L".png";

		shipDestroyed[i] = Surface::FromFile(filename);
	}
}

Surface* Animation::GetExplo()
{
	return explo;
}

Surface * Animation::GetShipDestroyed()
{
	return shipDestroyed;
}

Surface & Animation::GetMineSprite()
{
	return mineSprite;
}

Surface & Animation::GetShipSprite()
{
	return shipSprite;
}

Surface & Animation::GetHeartSprite()
{
	return heartSprite;
}

