#include "MainWindow.h"
#include "Mine.h"
#include "Ship.h"
#include "Surface.h"

Mine::Mine(float X, const Surface& MineSurface, Sound& Explosion, AnimationFrames& Anim)
	:
	surface(MineSurface),
	explo(Anim, 2.0f),
	explosion(Explosion),
	pos(X, resetY)
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
		pos.y += vy * Dt;
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
			gfx.DrawSpriteAlpha(int(pos.x), int(pos.y), surface);
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
	pos.y = resetY;
	hp = 60;
	mState = ActiveState;
	explo.Reset();
}

//float Mine::GetX() const
//{
//	return x;
//}
//
//float Mine::GetY() const
//{
//	return y;
//}
//
//float Mine::GetWidth() const
//{
//	return width;
//}
//
//float Mine::GetHeight() const
//{
//	return height;
//}