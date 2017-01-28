#pragma once
#include "Graphics.h"
#include "Bullet.h"

class Ship
{
public:
	void Draw(Graphics& gfx);
	void FireBullet();
	void ClampScreen();
	void Update(MainWindow& wnd);
	void PlayerInput(MainWindow& wnd);

private:
	int x = 300;
	int y = 300;
	int width = 100;
	int height = 100;
	int canonPos = 50;
	int vx = 5;
	int vy = 5;
	static constexpr int nBullets = 3;
	int bulletCounter = 0;
	Bullet bullet[nBullets];
	bool shotsFired = false;
};