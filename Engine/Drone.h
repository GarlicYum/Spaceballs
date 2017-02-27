#pragma once

#include "RectF.h"
#include "Vec2.h"
#include "Graphics.h"
#include "Animation.h"
#include "Sound.h"

class Drone
{
public:
	enum State
	{
		AliveState, DyingState, DeadState
	};
	Drone(float X, AnimationFrames& DroneAnim, AnimationFrames& DroneExplode, Sound& ExploSound);
	void Move(float dt);
	void Update(float dt);
	void Draw(Graphics& gfx);
	RectF GetCollisionRect() const;
	void Reset();
	void HandleCollision();
	int GetCollisionDmg() const;
	bool IsAlive() const;

private:
	Vec2 pos;
	float resetX;
	Vec2 vel = Vec2(360.0f, 300.0f);
	static constexpr float width = 80.0f;
	static constexpr float height = 40.0f;
	static constexpr int collisionDmg = 50;
	State state = AliveState;
	Animation droneAnim;
	Animation droneExplode;
	Sound& exploSound;
};