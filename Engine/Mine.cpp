#include "MainWindow.h"
#include "Mine.h"
#include "Ship.h"
#include "Surface.h"

Mine::Mine(float X, float Y, const Surface& MineSurface, Sound& Explosion, AnimationFrames& Anim)
	:
	surface(MineSurface),
	explo(Anim, 2.0f),
	explosion(Explosion),
	pos(X, Y),
	resetPos(X, Y)
{}

void Mine::HandleCollision(int dmg)
{
	hp -= dmg;
	switch (mState)
	{
	case MineState::ActiveState:
		if (hp <= 0)
		{
			damage = explDamage;
			SetState(Mine::DetonateState);
			explosion.Play();
		}
		break;
	case MineState::DetonateState:
		damage = 0;
		break;
	}
}

void Mine::Update(float Dt)
{
	switch (mState)
	{
	case MineState::ActiveState:
		if (pos.y + height <= 0.0f)
		{
			pos.y += offScreenVel * Dt;
		}
		else
		{
			pos.y += vy * Dt;
		}
		
		break;
	case MineState::DetonateState:
		explo.Advance(Dt);
		if (explo.AnimEnd())
			mState = InActiveState;
		break;
	}
}

void Mine::Draw(Graphics& gfx)
{
	switch (mState)
	{
	case ActiveState:
		if (pos.y < gfx.ScreenHeight)
		{
			gfx.DrawSpriteKey(int(pos.x), int(pos.y), surface, surface.GetPixel(0, 0));
		}
		break;
	case DetonateState:
		explo.Draw(int(pos.x), int(pos.y), gfx);
		break;
	}
}

int Mine::GetDamageCost() const
{
	return damage;
}

void Mine::SetState(MineState State)
{
	mState = State;
}

RectF Mine::GetCollisionRect() const
{
	return RectF(pos, width, height);
}

bool Mine::IsActive() const
{
	return mState == ActiveState;
}

void Mine::Reset()
{
	pos = resetPos;
	hp = 3;
	mState = ActiveState;
	explo.Reset();
}