#pragma once

#include "Animation.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "RectF.h"
#include "Sound.h"



class Mine
{
public:
	enum MineState
	{
		ActiveState, DetonateState, InActiveState
	};
	Mine( float X, const Surface &MineSurface, Sound &Explosion, AnimationFrames &Anim );
	void HandleCollision();
	void Update( float Dt );
	void Draw( Graphics& gfx );

	int GetDamageCost()const;
	void SetState( MineState State );
	RectF GetCollisionRect()const;
	bool IsActive()const;
private:
	static constexpr int explDamage = 75;
	static constexpr float width = 50.0f;
	static constexpr float height = 50.0f;
	Vec2 position = Vec2( 0.f, -50.f );
	float vy = 5.0f * 60.0f;
	MineState mState = ActiveState;
	const Surface &surface;
	Sound &explosion;
	Animation explo;
	bool gotPosition = false;
	int damage = 0;
};