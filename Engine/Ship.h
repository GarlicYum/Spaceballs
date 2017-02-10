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
	Ship(BulletManager& Manager, Surface& ShipSurface, Surface& exhaust, Surface& red);
	void HandleCollision(int Damage);
	void Draw(Graphics& gfx);
	void Update(Keyboard& wnd, float dt);
	void Restore(int restore);
	bool HasHealth() const;
	RectF GetCollisionRect() const;
	
	float GetX() const;
	float GetWidth() const;
	float GetY() const;
	float GetHeight() const;
	
	void SethitTarget(bool hit);
	void SetY(float Y);
	void SetX(float X);
	int GetDmg() const;

private:
	void PlayerInput(Keyboard& wnd, float dt);
	void ClampScreen();

private:
	bool hitTarget = false;
	float x = 300.0f;
	float y = 300.0f;
	float width = 90.0f;
	float height = 90.0f;
	static constexpr float canonX = 45.0f;
	static constexpr float canonY = 20.0f;
	float vx = 6.0f * 60.0f;
	float vy = 6.0f * 60.0f;
	Health health;
	bool healthChanging = false;
	float padding = 35.0f;
	BulletManager& bManager;
	Surface& shipSurface;
	Surface& exhaustSurface;
	Surface& redSurface;
	bool isMoving = false;
	static constexpr int dmg = 60;
	bool isHit = false;
	int isHitCounter = 0;
};