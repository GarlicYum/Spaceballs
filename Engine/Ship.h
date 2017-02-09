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
	Ship( BulletManager &Manager, Surface &ShipSurface );

	void HandleCollision( int Damage );
	void Draw(Graphics& gfx);
	void Update( Keyboard& wnd, float dt);
	void Restore(int restore);
	bool HasHealth() const;

	RectF GetCollisionRect()const;
	void SethitTarget(bool hit);

private:
	void PlayerInput( Keyboard& wnd, float dt );

private:
	void ClampScreen();

private:
	bool hitTarget = false;
	Vec2 position = Vec2( 300.f, 300.f );
	Vec2 cannonOffset = Vec2( 50.f, 20.f );
	Vec2 velocity = Vec2( 1.f, 1.f) * ( 6.f * 60.f );
	float width = 100.0f;
	float height = 100.0f;

	Health health;
	//bool healthChanging = false;
	//float padding = 35.0f;
	BulletManager &bManager;
	Surface &shipSurface;
};