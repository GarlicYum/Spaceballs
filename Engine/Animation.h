#pragma once
#include "Surface.h"
#include <string>
#include "Graphics.h"

class Animation
{
public:
	Animation();
	Surface* GetExplo();
	Surface* GetShipDestroyed();
	Surface& GetMineSprite();
	Surface& GetShipSprite();
	Surface& GetHeartSprite();
private:
	static constexpr int nExploFrames = 16;
	Surface explo[nExploFrames];
	static constexpr int nShipFrames = 20;
	Surface shipDestroyed[nShipFrames];
	Surface mineSprite = Surface::FromFile(L"mine.png");
	Surface shipSprite = Surface::FromFile(L"shippit.png");
	Surface heartSprite = Surface::FromFile(L"hart.png");

};