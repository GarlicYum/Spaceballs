#include "SmallEnemyShip.h"

SmallEnemyShip::SmallEnemyShip(float x, const Surface & enemySurface, AnimationFrames& smallexhaust)
	:
	pos(x, resetY),
	resetX(x),
	surface(enemySurface),
	smallExhaust(smallexhaust, 2)
{}

void SmallEnemyShip::MoveY(float dt)
{
	pos.y += (vel.y * dt);
}

void SmallEnemyShip::Update(float dt)
{
	if (state == AliveState)
	{
		MoveY(dt);

		if (coolDown)
		{
			if ((coolDownTime += dt) > coolDownOver)
			{
				coolDownTime = 0.0f;
				coolDown = false;
			}
		}

		smallExhaust.Advance();
		if (smallExhaust.AnimEnd())
		{
			smallExhaust.Reset();
		}

		if (hp <= 0)
		{
			state = DeadState;
		}
	}
}

void SmallEnemyShip::Draw(Graphics & gfx)
{
	if (hp > 0)
	{
		smallExhaust.Draw(int(pos.x), int(pos.y), gfx);
//		gfx.DrawSpriteKey(int(pos.x), int(pos.y), surface, surface.GetPixel(0, 0));
	}
}
	
RectF SmallEnemyShip::GetCollisionRect() const
{
	return RectF(pos, width, height);
}

void SmallEnemyShip::Reset()
{
	pos.y = resetY;
	pos.x = resetX;
	state = AliveState;
	hp = 80;
}

void SmallEnemyShip::HandleCollision(int dmg)
{
	hp -= dmg;
	coolDown = true;
}

int SmallEnemyShip::GetCollisionDmg() const
{
	return collisionDmg;
}

bool SmallEnemyShip::IsDead() const
{
	return state == DeadState;
}

bool SmallEnemyShip::GetCoolDown() const
{
	return coolDown;
}
