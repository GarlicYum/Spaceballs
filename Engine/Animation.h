#pragma once
#include "Surface.h"
#include <string>
#include "Graphics.h"

class Animation
{
public:
	Animation();
	Surface* GetExplo();
	Surface& GetMineSprite();
	Surface& GetShipSprite();
	Surface& GetHeartSprite();
private:
	static constexpr int surfCount = 16;
	Surface explo[surfCount];
	Surface mineSprite = Surface::FromFile(L"mine.png");
	Surface shipSprite = Surface::FromFile(L"shippit.png");
	Surface heartSprite = Surface::FromFile(L"hart.png");
};