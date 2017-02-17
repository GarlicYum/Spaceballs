#pragma once
#include "Bullet.h"
#include "Sound.h"
#include "Vec2.h"

class BulletManager
{
public:
	BulletManager() = default;
	const Bullet& GetBullet(int Idx) const;
	Bullet& GetBullet(int Idx);
	int GetNumBullets() const;

	void FireBullet(Vec2& canonPos, float Dt);
	void UpdateBullets(float Dt);
	void ResetShotsFired();
	void DrawBullets(class Graphics& Gfx);
	void Reset();

private:
	static constexpr int nBullets = 3;
	int bulletCounter = 0;
	Bullet bullets[nBullets];
	bool shotsFired = false;
	Sound gun = L"shitgun.wav";
};