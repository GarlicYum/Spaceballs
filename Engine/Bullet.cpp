#include "Bullet.h"

//constructor get the position of the bullet and sets the state to alive
Bullet::Bullet(float X, float Y)
	:
	x(X),
	y(Y),
	bState(AliveState)
{}

//Update makes the bullet move in y direction and changes state to deadstate if it reaches the end of the screen
void Bullet::Update(float dt)
{
	y -= vy * dt;

	if (y - bulletSize < 0)
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
	gfx.DrawCircle(int(x), int(y), bulletSize, Colors::Magenta);
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
		x - bSize,
		y - bSize,
		(bSize * 2.0f),
		(bSize * 2.0f));
}

void Bullet::HandleCollision()
{
	bState = DeadState;
}