#pragma once
#include "Graphics.h"
#include "RectF.h"
#include "Sound.h"
#include "Vec2.h"

class Shield
{
public:
	enum ShieldState
	{
		NewState, ActiveState, NoShield
	};

	void Update(class Ship& ship, Sound& shieldon, Sound& shieldoff);
	void Draw(Graphics& gfx) const;
	void DrawMeter(Graphics& gfx) const;
	bool GetisActive() const;
	void SetisActive(bool active);
	RectF GetCollisionRect() const;
	int GetDmg() const;
	void Reset();

private:
	Vec2 pos;
	static constexpr int radius = 90;
	ShieldState sState = NoShield;
	int shieldSize = 0;
	int holeSize = - 5;
	int meterWidth;
	static constexpr int meterHeight = 10;
	int meterX = 400;
	int meterY = 570;
	Color c = Colors::Blue;
	int meterCounter = 0;
	static constexpr int meterDecrease = 3;
	static constexpr int dmg = 60;
};