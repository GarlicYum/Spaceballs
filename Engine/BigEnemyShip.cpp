#include "BigEnemyShip.h"

BigEnemyShip::BigEnemyShip(float X, const Surface & surface, BulletManager& BulletM, AnimationFrames& ExploAnim, Sound& ExploSound, AnimationFrames& bulletAnim)
	:
	pos(X, -100.0f),
	shipSurface(surface),
	resetX(X),
	bulletM(BulletM),
	exploAnim(ExploAnim, 2.0f),
	exploSound(ExploSound),
	bulletSprite(bulletAnim, 2.0f),
	bulletTimer(1.5f),
	waitTimer(15.0f)
{}

void BigEnemyShip::Draw(Graphics & gfx)
{
	switch (state)
	{
	case AliveState:
		gfx.DrawSpriteAlpha(int(pos.x), int(pos.y), shipSurface);
		bulletM.DrawBullets(gfx, bulletSprite);
		break;
		
	case DyingState:
		exploAnim.Draw(int(pos.x), int(pos.y), gfx);
		break;
	}
}

void BigEnemyShip::Update(float dt)
{
	bulletM.UpdateBullets(dt, bulletSprite);
	switch (state)
	{
	case WaitState:
		if (waitTimer.Pause(dt))
		{
			waitTimer.Reset();
			state = AliveState;
		}
		break;
	case AliveState:
		Move(dt);
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
			state = WaitState;
		}
		break;
	}
}

void BigEnemyShip::Reset()
{
	pos.y = -100.0f;
	pos.x = resetX;
	hp = 600;
	state = WaitState;
	bulletTimer.Reset();
	exploAnim.Reset();
	vel.x = 100.0f;
	waitTimer.Reset();
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
	if (pos.y < 25.0f && !waitTimer.Pause(dt))
	{
		pos.y += vel.y * dt;
	}
	else if (!waitTimer.Pause(dt))
	{
		pos.x += vel.x * dt;
		Attack(dt);

		waitTimer.Increment(dt);
	}
	if ((pos.y > -100.0f) && waitTimer.PauseOver())
	{
		pos.y -= vel.y * dt;
	}
	else if (pos.y <= -100.0f)
	{
		Reset();
		state = WaitState;
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
