#include "BigEnemyShip.h"

BigEnemyShip::BigEnemyShip(float X, float Y, const Surface & surface, BulletManager& BulletM, AnimationFrames& ExploAnim, Sound& ExploSound)
	:
	pos(X, Y),
	resetPos(X, Y),
	shipSurface(surface),
	bulletM(BulletM),
	exploAnim(ExploAnim, 2.0f),
	exploSound(ExploSound),
	bulletTimer(1.5f),
	timer(15.0f),
	coolDownTimer(0.75f)
{}

void BigEnemyShip::Draw(Graphics & gfx)
{
	switch (state)
	{
	case AliveState:
		gfx.DrawSpriteKey(int(pos.x), int(pos.y), shipSurface, shipSurface.GetPixel(0, 0));
		break;
		
	case DyingState:
		exploAnim.Draw(int(pos.x), int(pos.y), gfx);
		break;
	}
}

void BigEnemyShip::Update(float dt)
{
	switch (state)
	{
	case AliveState:
		Move(dt);
		if (coolDown)
		{
			if (coolDownTimer.Pause(dt))
			{
				coolDown = false;
				coolDownTimer.Reset();
			}
		}
		if (hp <= 0)
		{
			exploSound.Play();
			state = DyingState;
		}
		break;

	case DyingState:
		exploAnim.Advance(dt);
		if (exploAnim.AnimEnd())
		{
			Reset();
			state = DeadState;
		}
		break;
	}
}

void BigEnemyShip::Reset()
{
	pos = resetPos;
	hp = 20;
	state = AliveState;
	bulletTimer.Reset();
	exploAnim.Reset();
	vel.x = 100.0f;
	timer.Reset();
	coolDownTimer.Reset();
}

RectF BigEnemyShip::GetCollisionRect() const
{
	return RectF(pos, width, height);
}

int BigEnemyShip::GetCollisionDmg() const
{
	return collisionDmg;
}

int BigEnemyShip::GetBulletDmg() const
{
	return bulletDmg;
}

void BigEnemyShip::HandleCollision(int dmg)
{
	if (state == AliveState)
	{
		hp -= dmg;
		coolDown = true;
	}
}

void BigEnemyShip::Attack(float dt)
{
	if (bulletTimer.Pause(dt))
	{
		Vec2 canonPos = pos + canon;
		bulletTimer.Reset();
		bulletM.FireBullet(canonPos, bulletVel, bulletHalfWidth, bulletHalfHeight, bulletRectSize, bulletDmg, bulletPitch);
		bulletM.ResetShotsFired();
	}
}

void BigEnemyShip::Move(float dt)
{
	if (pos.y < 25.0f)
	{
		pos.y += vel.y * dt;
	}
	else if (!timer.Pause(dt))
	{
		pos.x += vel.x * dt;
		Attack(dt);

		timer.Increment(dt);
	}
	if ((pos.y < Graphics::ScreenHeight) && timer.PauseOver())
	{
		pos.y += vel.y * dt;
	}
	else if (pos.y > Graphics::ScreenHeight)
	{
		Reset();
		state = DeadState;
	}

	if ((pos.x <= 0 && vel.x < 0.0f) ||
		((pos.x + width) >= Graphics::ScreenWidth && vel.x > 0.0f))
	{
		vel.x = -vel.x;
	}
}

bool BigEnemyShip::IsAlive() const
{
	return state == AliveState;
}

bool BigEnemyShip::GetCoolDown() const
{
	return coolDown;
}
