#include "SmallEnemyShip.h"

SmallEnemyShip::SmallEnemyShip(float x, float y, AnimationFrames& smallexhaust, AnimationFrames& smallexplode, Sound& smallexplo, 
	BulletManager& smallLeftManager, BulletManager& smallRightManager, const Surface& FlashSurface)
	:
	pos(x, y),
	resetPos(x, y),
	smallExhaust(smallexhaust, 2.0f),
	smallExplode(smallexplode, 3.0f),
	smallExploSound(smallexplo),
	smallLeftM(smallLeftManager),
	smallRightM(smallRightManager),
	bulletTimer(0.5f),
	coolDownTimer(0.75f),
	hitTimer(0.05f),
	flashSurface(FlashSurface)
{}

void SmallEnemyShip::Attack(float dt)
{
	if ((pos.y + height) < Graphics::ScreenHeight && (pos.y + leftCanon.y) > 0.0f)
	{
		Vec2 leftCanonPos = pos + leftCanon;
		Vec2 rightCanonPos = pos + rightCanon;
		if (bulletTimer.Pause(dt))
		{
			smallLeftM.FireBullet(leftCanonPos, bulletVel, bulletHalfWidth, bulletHalfHeight, bulletRectSize, bulletDmg, bulletPitch);
			smallRightM.FireBullet(rightCanonPos, bulletVel, bulletHalfWidth, bulletHalfHeight, bulletRectSize, bulletDmg, bulletPitch);
			smallLeftM.ResetShotsFired();
			smallRightM.ResetShotsFired();
			bulletTimer.Reset();
		}
	}
}

void SmallEnemyShip::Move(float dt, float playerX)
{
	
	if (pos.y + height >= 0.0f)
	{
		pos.y += vel.y * dt;
		pos.x += vel.x * dt;
		if ((playerX - 200.0f) > pos.x)
		{
			vel.x = 100.0f;
		}
		else if ((playerX + 200.0f) < pos.x)
		{
			vel.x = -100.0f;
		}
		else
		{
			Attack(dt);
		}

		if (pos.x < 0.0f || (pos.x + width) > int(Graphics::ScreenWidth))
		{
			vel.x = -vel.x;
		}
	}
	else
	{
		pos.y += offScreenVel * dt;
	}
}

void SmallEnemyShip::Update(float dt, float playerX)
{
	switch (state)
	{
	case AliveState:
		Move(dt, playerX);
		if (coolDown)
		{
			if (coolDownTimer.Pause(dt))
			{
				coolDownTimer.Reset();
				coolDown = false;
			}
		}

		if (isHit)
		{
			if (hitTimer.Pause(dt))
			{
				isHit = false;
				hitTimer.Reset();
			}
		}

		smallExhaust.Advance(dt);
		if (smallExhaust.AnimEnd())
		{
			smallExhaust.Reset();
		}

		if (hp <= 0)
		{
			state = DyingState;
			smallExploSound.Play(0.7f, 2.0f);
		}

		if (pos.y > Graphics::ScreenHeight)
		{
			state = DeadState;
		}
		break;

	case DyingState:
		smallExplode.Advance(dt);

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
		if (isHit)
		{
			gfx.DrawSpriteKey(int(pos.x), int(pos.y), flashSurface, flashSurface.GetPixel(0, 0));
		}
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
	pos = resetPos;
	smallExplode.Reset();
	state = AliveState;
	hp = 3;
	bulletTimer.Reset();
	coolDownTimer.Reset();
}

void SmallEnemyShip::HandleCollision(int dmg)
{
	hp -= dmg;
	coolDown = true;
	isHit = true;
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
