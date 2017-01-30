#pragma once
#include "Graphics.h"
#include "Bullet.h"
#include "Sound.h"
#include "Health.h"

class Ship
{
public:
	void Draw(Graphics& gfx);
	void FireBullet();
	void ClampScreen();
	void Update(MainWindow& wnd);
	void PlayerInput(MainWindow& wnd);
	void Restore(int restore);
	void Damage(int damage);
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

private:
	int x = 300;
	int y = 300;
	int width = 100;
	int height = 100;
	int canonPos = 50;
	int vx = 6;
	int vy = 6;
	static constexpr int nBullets = 3;
	int bulletCounter = 0;
	Bullet bullet[nBullets];
	bool shotsFired = false;
	Sound gun = L"shitgun.wav";
	Health health;
	bool healthChanging = false;
	int padding = 35;
};