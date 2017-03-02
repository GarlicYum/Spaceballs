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
	void HandleCollision(int damage);

private:
	Vec2 pos;
	static constexpr float radius = 90.0f;
	ShieldState sState = NoShield;
	float shieldSize = 0.0f;
	float holeSize = - 5.0f;
	int meterWidth;
	static constexpr int meterHeight = 10;
	int meterX = 400;
	int meterY = 570;
	Color c = Colors::Blue;
	static constexpr int dmg = 60;
};