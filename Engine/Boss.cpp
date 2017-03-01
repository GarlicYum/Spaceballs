#include "Boss.h"

Boss::Boss(AnimationFrames & bossAnim, BulletManager& BulletM)
	:
bossSprite(bossAnim, 2),
bulletM(BulletM)
{}

void Boss::Update(float dt)
{
	switch (state)
	{
	case EntranceState:
		Move(dt);

		bossSprite.Advance();
		if (bossSprite.AnimEnd())
		{
			bossSprite.Reset();
		}
		break;

	case AliveState:
		Move(dt);

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
		break;

	case ExplodingState:
		break;
	}
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
}

int Boss::GetCollisionDmg() const
{
	return collisionDmg;
}

RectF Boss::GetCollisionRect() const
{
	return RectF(pos, width, height);
}

void Boss::Move(float dt)
{
	if (state == EntranceState)
	{
		if (int(pos.y) < 15)
		{
			pos.y += entranceSpeed * dt;
		}
		else
		{
			// insert timer, to wait for health bar to fill etc
			state = AliveState;
		}
	}
}

void Boss::HandleCollision(int dmg)
{
	coolDown = true;
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

void Boss::Reset()
{
	state = EntranceState;
	pos.x = 315.0f;
	pos.y = -250.0f;
}
