#include "SmallEnemyShip.h"

SmallEnemyShip::SmallEnemyShip(float x, const Surface & enemySurface, AnimationFrames& smallexhaust, AnimationFrames& smallexplode, Sound& smallexplo)
	:
	pos(x, -100.0f),
	resetX(x),
	surface(enemySurface),
	smallExhaust(smallexhaust, 2),
	smallExplode(smallexplode, 3),
	smallExploSound(smallexplo)
{}

void SmallEnemyShip::MoveY(float dt)
{
	pos.y += (vel.y * dt);
}

void SmallEnemyShip::Update(float dt)
{
	MoveY(dt);

	switch (state)
	{
	case AliveState:
		
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
			state = DyingState;
			smallExploSound.Play(0.7f, 2.0f);
		}

		break;

	case DyingState:
		smallExplode.Advance();

		if (smallExplode.AnimEnd())
		{
			state = DeadState;
		}

		break;
	}
}

void SmallEnemyShip::Draw(Graphics & gfx)
{
	switch (state)
	{
	case AliveState:
		smallExhaust.Draw(int(pos.x), int(pos.y), gfx);
//		gfx.DrawSpriteKey(int(pos.x), int(pos.y), surface, surface.GetPixel(0, 0));
		
		break;

	case DyingState:
		smallExplode.Draw(int(pos.x), int(pos.y), gfx);
		break;
	}
}
	
RectF SmallEnemyShip::GetCollisionRect() const
{
	return RectF(pos, width, height);
}

void SmallEnemyShip::Reset()
{
	pos.y = -100.0f;
	pos.x = resetX;
	smallExplode.Reset();
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

bool SmallEnemyShip::IsAlive() const
{
	return state == AliveState;
}

bool SmallEnemyShip::GetCoolDown() const
{
	return coolDown;
}
