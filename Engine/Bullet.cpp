#include "Bullet.h"

//constructor get the position of the bullet and sets the state to alive
Bullet::Bullet(Vec2& pos_in)
	:
	pos(pos_in),
	bState(AliveState)
{}

Bullet::Bullet(Vec2 & pos_in, Vec2& Vel, int Width, int Height, int bulletRectSize, int Dmg)
	:
	pos(pos_in),
	halfWidth(Width),
	halfHeight(Height),
	vel(Vel),
	dmg(Dmg),
	bState(AliveState),
	rectSize(bulletRectSize)
{}

//Update makes the bullet move in y direction and changes state to deadstate if it reaches the end of the screen
void Bullet::Update(float dt, Animation& bulletSprite)
{
	pos -= vel * dt;

	bulletSprite.Advance(dt);
	if (bulletSprite.AnimEnd())
	{
		bulletSprite.Reset();
	}

	if ((pos.y + (halfHeight * 2)) < 0 || pos.y >= Graphics::ScreenHeight)
	{
		bState = DeadState;
	}
}

//if bState == alivestate then hasspawned returns true, else it returns false
bool Bullet::HasSpawned() const
{
	return bState == AliveState;
}

void Bullet::Draw(Graphics& gfx, Animation& bulletSprite)
{
	bulletSprite.Draw(int(pos.x), int(pos.y), gfx);
}

bool Bullet::IsActive() const
{
	return bState == AliveState;
}

RectF Bullet::GetCollisionRect() const
{
	Vec2 center = Vec2(pos.x + float(halfWidth), pos.y + float(halfHeight));
	Vec2 rectPos = Vec2(center.x - float(rectSize), center.y - float(rectSize));
	return RectF(rectPos, float(rectSize * 2), float(rectSize * 2));
}

void Bullet::HandleCollision()
{
	bState = DeadState;
}

int Bullet::GetDamage()
{
	return dmg;
}

int Bullet::GetBossDmg()
{
	return bossDmg;
}

void Bullet::Reset()
{
	bState = DeadState;
}
