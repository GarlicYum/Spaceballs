#include "Boss.h"

Boss::Boss(AnimationFrames & bossAnim, BulletManager& LeftBulletM, BulletManager& RightBulletM, BulletManager& CenterBulletM, 
	AnimationFrames& BulletAnim, AnimationFrames& lightBallAnim, AnimationFrames& bossExploAnim, AnimationFrames& bossPreExploAnim,
	Sound& shipExplodeSound)
	:
bossSprite(bossAnim, 2.0f),
bulletSprite(BulletAnim, 2.0f),
rightBulletM(RightBulletM),
leftBulletM(LeftBulletM),
centerBulletM(CenterBulletM),
health(healthX, healthY, 0),
lightBall(lightBallAnim, 2.0f),
bossExplo(bossExploAnim, 2.0f),
bossPreExplo(bossPreExploAnim, 2.0f),
bigExploSound(shipExplodeSound),
attackTimer(1.0f),
specAttackTimer(5.0f),
lightBallTimer(0.3f),
coolDownTimer(0.75f),
waitTimer(0.5f),
vibrationTimer(0.05f)
{}

void Boss::Update(float dt, float playerPos)
{
	switch (state)
	{
	case EntranceState:
		Move(dt, playerPos);

		bossSprite.Advance(dt);
if (bossSprite.AnimEnd())
{
	bossSprite.Reset();
}
break;

	case AliveState:
		Move(dt, playerPos);

		bossSprite.Advance(dt);
		if (bossSprite.AnimEnd())
		{
			bossSprite.Reset();
		}

		if (coolDown)
		{
			if (coolDownTimer.Pause(dt))
			{
				coolDown = false;
				coolDownTimer.Reset();
			}
		}

		if (health.GetHealthAmount() <= 100)
		{
			specAttackTimer.SetWaitTime(3.0f);
			thrustY = 450.0f;
			thrustLeft = -450.0f;
			thrustRight = 450.0f;
			speedFactor = 2.0f;
		}
		else if (health.GetHealthAmount() <= 200)
		{
			specAttackTimer.SetWaitTime(4.0f);
			thrustY = 375.0f;
			thrustLeft = -375.0f;
			thrustRight = 375.0f;
			speedFactor = 1.5f;
		}

		if (!health.HasHealth())
		{
			state = ExplodingState;
		}
		break;

	case ExplodingState:
		if (isNotExploding)
		{
			if (waitTimer.Pause(dt))
			{
				BringToCenter(dt);
			}
		}
		else
		{
			if (exploCounter < 6)
			{
				Vibrate(dt);
				bossPreExplo.Advance(dt);
				if (bossPreExplo.AnimEnd())
				{
					bossPreExplo.Reset();
					++exploCounter;
				}
			}

			else
			{
				if (!bigExploSoundPlayed)
				{
					bigExploSoundPlayed = true;
					bigExploSound.Play(0.9f, 1.0f);
				}
				bossExplo.Advance(dt);
				if (bossExplo.AnimEnd())
				{
					bossExplo.Reset();
					state = DeadState;
				}
			}
		}		
		break;
	}
	leftBulletM.UpdateBullets(dt, bulletSprite);
	rightBulletM.UpdateBullets(dt, bulletSprite);
	centerBulletM.UpdateBullets(dt, lightBall);
}

void Boss::Draw(Graphics & gfx)
{
	centerBulletM.DrawBullets(gfx, lightBall);
	leftBulletM.DrawBullets(gfx, bulletSprite);
	rightBulletM.DrawBullets(gfx, bulletSprite);
	switch (state)
	{
	case EntranceState:
		bossSprite.Draw(int(pos.x), int(pos.y), gfx);
		break;
	case AliveState:
		bossSprite.Draw(int(pos.x), int(pos.y), gfx);
		break;
	case ExplodingState:
		if (isNotExploding)
		{
			bossSprite.Draw(int(pos.x), int(pos.y), gfx);
		}
		else
		{
			if (exploCounter < 6)
			{
				bossPreExplo.Draw(int(pos.x), int(pos.y), gfx);
			}
			else
			{
				bossExplo.Draw(-1, 0, gfx);
			}
		}
		break;
	}
	health.Draw(gfx);
}

int Boss::GetCollisionDmg() const
{
	return collisionDmg;
}

void Boss::Attack(float dt, float playerPos, short choice)
{
	switch (choice)
	{
	case 1:
		Thrust(dt, playerPos);
		break;
	case 2:
		BulletSpread(dt, playerPos);
		break;
	}
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

RectF Boss::GetCollisionRect() const
{
	return RectF(pos, width, height);
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
		BringBack(dt);
	}
}

void Boss::BulletSpread(float dt, float playerPos)
{
	Vec2 canonPos = pos + centerCanon;

	if (lightBallTimer.Pause(dt))
	{
		if (!hasPlayerPos)
		{
			if (playerPos <= GetCollisionRect().GetCenterX())
			{
				lightBallDir = -400.0f;
				lightBallIncrement = 126.0f;
			}
			else
			{
				lightBallDir = 400.0f;
				lightBallIncrement = -126.0f;
			}
			hasPlayerPos = true;
		}

		Vec2 dest = Vec2(lightBallDir, 600.0f);
		Vec2 diff = centerCanon - dest;
		diff *= 1.3f;

		centerBulletM.FireBullet(canonPos, diff, bulletHalfWidth, bulletHalfHeight, bulletRectSize, bulletDmg, bulletPitch);
		centerBulletM.ResetShotsFired();
		lightBallTimer.Reset();
		++lightBallCounter;
		lightBallDir += lightBallIncrement;
	}

	if (lightBallCounter == 8)
	{
		lightBallCounter = 0;
		lightBallTimer.Reset();
		isAttacking = false;
		lightBallDir = -400.0f;
		specAttackTimer.Reset();
		choiceWasMade = false;
		hasPlayerPos = false;
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
			if (health.FillUp(hp, 2, dt))
				state = AliveState;
		}
	}

	if (state == AliveState)
	{
		if (!isAttacking)
		{
			pos.x -= ((vel.x * dt) * speedFactor);
			if (pos.x <= 0.0f)
			{
				pos.x = 0.0f;
				vel.x = -vel.x;
			}	
			else if ((pos.x + width) >= Graphics::ScreenWidth)
			{
				pos.x = Graphics::ScreenWidth - width;
				vel.x = -vel.x;
			}

			if (attackTimer.Pause(dt))
			{
				Vec2 leftCanonPos = pos + leftCanon;
				Vec2 rightCanonPos = pos + rightCanon;
				leftBulletM.FireBullet(leftCanonPos, bulletVel, bulletHalfWidth, bulletHalfHeight, bulletRectSize, bulletDmg, bulletPitch);
				rightBulletM.FireBullet(rightCanonPos, bulletVel, bulletHalfWidth, bulletHalfHeight, bulletRectSize, bulletDmg, bulletPitch);
				leftBulletM.ResetShotsFired();
				rightBulletM.ResetShotsFired();
				attackTimer.Reset();
			}
		}

		if (specAttackTimer.Pause(dt))
		{
			if (!choiceWasMade)
			{
				std::random_device rd;
				std::mt19937 rng(rd());
				std::uniform_int_distribution<short> Choice(1, 2);
				AttackChoice = Choice(rng);
				choiceWasMade = true;
			}
			isAttacking = true;
			Attack(dt, playerPos, AttackChoice);
			attackTimer.Reset();
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

void Boss::BringBack(float dt)
{
	const RectF bossRect = GetCollisionRect();
	bossCenter = bossRect.GetCenter();
	Vec2 diff = bossCenter - midPoint;

	if (diff.GetLengthSq() > 5.0f)
	{
		diff.Normalize();
		diff *= 210.0f;
		pos -= diff * dt;
	}
	else
	{
		attackOver = false;
		isAttacking = false;
		specAttackTimer.Reset();
		choiceWasMade = false;
	}
}

void Boss::BringToCenter(float dt)
{
	const RectF bossRect = GetCollisionRect();
	bossCenter = bossRect.GetCenter();
	Vec2 diff = bossCenter - screenCenter;

	if (diff.GetLengthSq() > 5.0f)
	{
		diff.Normalize();
		diff *= 210.0f;
		pos -= diff * dt;
	}
	else
	{
		waitTimer.Reset();
		isNotExploding = false;
	}
}

bool Boss::IsExploding() const
{
	return state == ExplodingState;
}

bool Boss::IsDead() const
{
	return state == DeadState;
}

void Boss::Vibrate(float dt)
{
	pos.x += vel.x * dt;
	if (vibrationTimer.Pause(dt))
	{
		vel.x = -vel.x;
		vibrationTimer.Reset();
	}
}

void Boss::Reset()
{
	state = EntranceState;
	vibrationTimer.Reset();
	pos.x = 315.0f;
	pos.y = -250.0f;
	vel.x = 100.0f;
	attackTimer.Reset();
	specAttackTimer.Reset();
	health.Damage(health.GetHealthAmount());
	isAttacking = false;
	attackOver = false;
	hasPlayerPos = false;
	choiceWasMade = false;
	lightBallCounter = 0;
	lightBallTimer.Reset();
	isNotExploding = true;
	exploCounter = 0;
	waitTimer.Reset();
	specAttackTimer.SetWaitTime(5.0f);
	thrustY = 300.0f;
	thrustLeft = -300.0f;
	thrustRight = 300.0f;
	speedFactor = 1.0f;
	bigExploSoundPlayed = false;
}
