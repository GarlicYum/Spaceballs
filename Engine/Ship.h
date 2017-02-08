#pragma once
#include "Graphics.h"
#include "BulletManager.h"
#include "Health.h"
#include "Keyboard.h"
#include "RectF.h"
#include "Sound.h"
#include "Vec2.h"

class Ship
{
public:
	Ship(BulletManager& Manager, Surface& ShipSurface);
	void HandleCollision(int Damage);
	void Draw(Graphics& gfx);
	void Update(Keyboard& wnd, float dt);
	void Restore(int restore);
	bool HasHealth() const;
	RectF GetCollisionRect() const;
	/*float GetX() const;
	float GetY() const;
	float GetWidth() const;
	float GetHeight() const;*/
	void SethitTarget(bool hit);

private:
	void PlayerInput(Keyboard& wnd, float dt);
	void ClampScreen();

private:
	bool hitTarget = false;
	float x = 300.0f;
	float y = 300.0f;
	float width = 100.0f;
	float height = 100.0f;
	float canonX = 50.0f;
	float canonY = 20.0f;
	float vx = 6.0f * 60.0f;
	float vy = 6.0f * 60.0f;
	Health health;
	bool healthChanging = false;
	float padding = 35.0f;
	BulletManager& bManager;
	Surface& shipSurface;
};