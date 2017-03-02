#include "Boss.h"

Boss::Boss(AnimationFrames & bossAnim, BulletManager& LeftBulletM, BulletManager& RightBulletM, AnimationFrames& BulletAnim)
	:
bossSprite(bossAnim, 2),
bulletSprite(BulletAnim, 2),
rightBulletM(RightBulletM),
leftBulletM(LeftBulletM),
health(healthX, healthY, 0)
{}

void Boss::Update(float dt, float playerPos)
{
	switch (state)
	{
	case EntranceState:
		Move(dt, playerPos);

		bossSprite.Advance();
if (bossSprite.AnimEnd())
{
	bossSprite.Reset();
}
break;

	case AliveState:
		Move(dt, playerPos);

		bossSprite.Advance();
		if (bossSprite.AnimEnd())
		{
			bossSprite.Reset();
		}

		if (coolDown)
		{
			if ((coolDownTimer += dt) > coolDownOver)
			{
				coolDown = false;
				coolDownTimer = 0.0f;
			}
		}

		if (!health.HasHealth())
		{
			state = ExplodingState;
		}
		break;

	case ExplodingState:
		break;
	}
	leftBulletM.UpdateBullets(dt, bulletSprite);
	rightBulletM.UpdateBullets(dt, bulletSprite);
}

void Boss::Draw(Graphics & gfx)
{
	switch (state)
	{
	case EntranceState:
		bossSprite.Draw(int(pos.x), int(pos.y), gfx);
		break;
	case AliveState:
		bossSprite.Draw(int(pos.x), int(pos.y), gfx);
		break;
	case ExplodingState:
		break;
	}
	leftBulletM.DrawBullets(gfx, bulletSprite);
	rightBulletM.DrawBullets(gfx, bulletSprite);
	health.Draw(gfx);
}

int Boss::GetCollisionDmg() const
{
	return collisionDmg;
}

RectF Boss::GetBottomCollisionRect() const
{
	return RectF(Vec2(pos.x + 10, pos.y + height - 1), width - 20, 1);
}

RectF Boss::GetTopCollisionRect() const
{
	return RectF(Vec2(pos.x + 10, pos.y), width - 20, 1);
}

RectF Boss::GetLeftCollisionRect() const
{
	return RectF(pos, 1, height);
}

RectF Boss::GetRightCollisionRect() const
{
	return RectF(Vec2(pos.x + width - 1, pos.y), 1, height);
}

void Boss::Thrust(float dt, float playerPos)
{
	if (((pos.y + height) < Graphics::ScreenHeight) && !attackOver)
	{
		pos.y += thrustY * dt;
	}
	else if (!attackOver)
	{
		if (!hasPlayerPos)
		{
			if (playerPos <= pos.x)
			{
				thrustX = thrustLeft;
			}
			else
			{
				thrustX = thrustRight;
			}
			hasPlayerPos = true;
		}
		pos.x += thrustX * dt;
	}

	if (pos.x <= 0.0f || ((pos.x + width) >= Graphics::ScreenWidth) && !attackOver)
	{
		attackOver = true;
		hasPlayerPos = false;
		
	}
	if (attackOver)
	{
		BringBack();
	}
}

void Boss::Move(float dt, float playerPos)
{
	if (state == EntranceState)
	{
		if (int(pos.y) < 15)
		{
			pos.y += entranceSpeed * dt;
		}
		else
		{
			if (health.FillUp(hp, 2))
				state = AliveState;
		}
	}

	if (state == AliveState)
	{
		if (!isAttacking)
		{
			pos.x -= vel.x * dt;
			if (pos.x <= 0.0f || (pos.x + width) >= Graphics::ScreenWidth)
			{
				vel.x = -vel.x;
			}	

			if ((attackTimer += dt) > attack)
			{
				Vec2 leftCanonPos = pos + leftCanon;
				Vec2 rightCanonPos = pos + rightCanon;
				leftBulletM.FireBullet(leftCanonPos, bulletVel, bulletHalfWidth, bulletHalfHeight, bulletRectSize, bulletDmg, bulletPitch);
				rightBulletM.FireBullet(rightCanonPos, bulletVel, bulletHalfWidth, bulletHalfHeight, bulletRectSize, bulletDmg, bulletPitch);
				leftBulletM.ResetShotsFired();
				rightBulletM.ResetShotsFired();
				attackTimer = 0.0f;
			}
		}

		if ((specialAttackTimer += dt) > specialAttack)
		{
			isAttacking = true;
			Thrust(dt, playerPos);
		}
	}
}

void Boss::HandleCollision(int dmg)
{
	coolDown = true;
	health.Damage(dmg);
}

bool Boss::GetCoolDown() const
{
	return coolDown;
}

bool Boss::IsEntering() const
{
	return state == EntranceState;
}

bool Boss::IsAliveState() const
{
	return state == AliveState;
}

float Boss::GetLeft() const
{
	return pos.x;
}

float Boss::GetRight() const
{
	return pos.x + width;
}

float Boss::GetTop() const
{
	return pos.y;
}

float Boss::GetBottom() const
{
	return pos.y + height;
}

void Boss::BringBack()
{
	RectF bossRect = RectF(pos, width, height);
	bossCenter = bossRect.GetCenter();
	Vec2 diff = bossCenter - midPoint;

	if (diff.GetLengthSq() > 5.0f)
	{
		diff.Normalize();
		diff *= 3.5f;
		pos -= diff;
	}
	else
	{
		attackOver = false;
		isAttacking = false;
		specialAttackTimer = 0.0f;
	}
}

void Boss::Reset()
{
	state = EntranceState;
	pos.x = 315.0f;
	pos.y = -250.0f;
	vel.x = 100.0f;
	attackTimer = 0.0f;
	specialAttackTimer = 0.0f;
	health.Damage(health.GetHealthAmount());
	isAttacking = false;
	attackOver = false;
	hasPlayerPos = false;
}
