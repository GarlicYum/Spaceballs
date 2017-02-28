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
