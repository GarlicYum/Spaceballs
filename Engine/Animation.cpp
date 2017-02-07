#include "Animation.h"

Animation::Animation()
{
	std::wstring filename;
	for (int i = 0; i < surfCount; ++i)
	{
		const int j = i + 1;

		filename = L"mineExplo\\" + std::to_wstring(j) + L".png";

		explo[i] = Surface::FromFile(filename);
	}
}

Surface* Animation::GetExplo()
{
	return explo;
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

