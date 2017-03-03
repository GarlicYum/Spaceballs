#pragma once
#include "Bullet.h"
#include "Sound.h"
#include "Vec2.h"
#include "Animation.h"

class BulletManager
{
public:
	BulletManager() = default;
	const Bullet& GetBullet(int Idx) const;
	Bullet& GetBullet(int Idx);
	int GetNumBullets() const;
	void FireBullet(Vec2& canonPos);
	void FireBullet(Vec2& canonPos, Vec2& vel, int bulletWidth, int bulletHeight, int bulletRectSize, int Dmg, float pitch);
	void UpdateBullets(float Dt, Animation& bulletSprite);
	void ResetShotsFired();
	void DrawBullets(class Graphics& Gfx, Animation& bulletSprite);
	void Reset();

private:
	static constexpr int nBullets = 4;
	int bulletCounter = 0;
	Bullet bullets[nBullets];
	bool shotsFired = false;
	Sound gun = L"shitgun.wav";
};