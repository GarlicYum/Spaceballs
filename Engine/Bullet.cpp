#include "Bullet.h"

//constructor get the position of the bullet and sets the state to alive
Bullet::Bullet(Vec2& pos_in)
	:
	pos(pos_in),
	bState(AliveState)
{}

//Update makes the bullet move in y direction and changes state to deadstate if it reaches the end of the screen
void Bullet::Update(float dt)
{
	pos.y -= vy * dt;

	if (pos.y - bulletSize < 0)
	{
		bState = DeadState;
	}
}

//if bState == alivestate then hasspawned returns true, else it returns false
bool Bullet::HasSpawned() const
{
	return bState == AliveState;
}

void Bullet::Draw(Graphics& gfx)
{
	gfx.DrawCircle(int(pos.x), int(pos.y), bulletSize, Colors::Magenta);
}

bool Bullet::IsActive() const
{
	return bState == AliveState;
}

//returns RectF based on bullets position and size
RectF Bullet::GetCollisionRect() const
{
	const float bSize = float(bulletSize);
	return RectF(
		Vec2(pos.x - bSize, pos.y - bSize),
		(bSize * 2.0f),
		(bSize * 2.0f));
}

void Bullet::HandleCollision()
{
	bState = DeadState;
}

int Bullet::GetDamage()
{
	return dmg;
}

void Bullet::Reset()
{
	bState = DeadState;
}
