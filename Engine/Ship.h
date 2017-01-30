#pragma once
#include "Graphics.h"
#include "Bullet.h"
#include "Sound.h"
#include "Health.h"

class Ship
{
public:
	void Draw(Graphics& gfx);
	void FireBullet(float dt);
	void ClampScreen();
	void Update(MainWindow& wnd, float dt);
	void PlayerInput(MainWindow& wnd, float dt);
	void Restore(int restore);
	void Damage(int damage);
	bool HasHealth() const;
	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();

private:
	float x = 300.0f;
	float y = 300.0f;
	float width = 100.0f;
	float height = 100.0f;
	float canonPos = 50.0f;
	float vx = 6.0f * 60.0f;
	float vy = 6.0f * 60.0f;
	static constexpr int nBullets = 3;
	int bulletCounter = 0;
	Bullet bullet[nBullets];
	bool shotsFired = false;
	Sound gun = L"shitgun.wav";
	Health health;
	bool healthChanging = false;
	float padding = 35.0f;
};