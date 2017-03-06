#pragma once
#include "Graphics.h"
#include "BulletManager.h"
#include "Health.h"
#include "Keyboard.h"
#include "RectF.h"
#include "Sound.h"
#include "Vec2.h"
#include "Animation.h"

class Ship
{
public:
	enum ShipState
	{
		AliveState, ExplodingState, BlackHoleTransitionState, TransitionBackState, BlackHoleState, DeadState
	};
	Ship(BulletManager& Manager, Surface& ShipSurface, 
		Surface& red, AnimationFrames& shiprekt, 
		AnimationFrames& holeAnim, AnimationFrames& holeRektAnim, AnimationFrames& shipexplo, 
		AnimationFrames& exhaustAnim, AnimationFrames& rektExhaustAnim, Sound& shipexplodesound, Sound& blackholesound, AnimationFrames& bulletAnim);
	void HandleCollision(int Damage, float dt);
	void Draw(Graphics& gfx);
	void Update(Keyboard& wnd, float dt);
	void Restore(int restore);
	bool IsAlive() const;
	bool IsDead() const;
	bool IsBlackHole() const;
	bool ExitingBlackHole() const;
	void EnableInput();
	RectF GetCollisionRect();
	
	float GetX() const;
	float GetWidth() const;
	float GetY() const;
	float GetHeight() const;
	int GetHealth() const;
	
	void SethitTarget(bool hit);
	void AddGravity(Vec2& gravity, float dt);
	void SetY(float Y);
	void SetX(float X);
	int GetDmg() const;
	void CollidesWithHole(bool collides);
	void PrepareForBoss(float dt);
	float GetRight() const;
	float GetBottom() const;
	bool FlyOffScreen(float dt);
	void Reset();

private:
	void PlayerInput(Keyboard& wnd, float dt);
	void ClampScreen();

private:
	bool hitTarget = false;
	Vec2 pos = Vec2(300.0f, 300.0f);
	static constexpr float canonX = 25.0f;
	static constexpr float canonY = -20.0f;
	float speed = 360.0f;
	float width = 90.0f;
	float height = 90.0f;
	static constexpr float hitOver = 10.0f / 60.0f;
	Health health;
	float padding = 35.0f;
	BulletManager& bManager;
	Surface& shipSurface;
	Surface& redSurface;
	bool isMoving = false;
	static constexpr int dmg = 60;
	float isHitCounter = 0.0f;
	Animation shipRekt;
	static constexpr int lowHealth = 75;
	bool isHit = false;
	Animation blackHole;
	Animation blackHoleRekt;
	Animation shipExplo;
	Animation exhaust;
	Animation rektExhaust;
	static constexpr int exploX = 196;
	static constexpr int exploY = 239;
	Sound& shipExplodeSound;
	ShipState state = AliveState;
	Sound& blackHoleSound;
	float oldX;
	float oldY;
	bool firstTransition = true;
	Animation bulletSprite;
	bool inputEnabled = true;
	bool gameComplete = false;
};