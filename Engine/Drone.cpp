#include "Drone.h"

Drone::Drone(float X, AnimationFrames & DroneAnim, AnimationFrames & DroneExplode, Sound & ExploSound)
	:
	pos(X, -40.0f),
	resetX(X),
	droneAnim(DroneAnim, 2),
	droneExplode(DroneExplode, 2),
	exploSound(ExploSound)
{}

void Drone::Move(float dt)
{
	pos.y += vel.y;
	pos.x += vel.x;

	if (vel.x >= 0.0f && vel.x <= 8.0f && accelerating)
	{
		vel.x += 0.4f;
	}
	else if (vel.x >= 0.0f)
	{
		accelerating = false;
		vel.x -= 0.4f;
	}
	else if (vel.x < 0.0f && vel.x >= -8.0f && !accelerating)
	{
		vel.x -= 0.4f;
	}
	else if (vel.x < 0.0f)
	{
		accelerating = true;
		vel.x += 0.4f;
	}	
}

void Drone::Update(float dt)
{
	switch (state)
	{
	case AliveState:
		Move(dt);
		droneAnim.Advance();
		if (droneAnim.AnimEnd())
		{
			droneAnim.Reset();
		}
		if (pos.y > Graphics::ScreenHeight)
		{
			state = DeadState;
		}
		break;

//	case DyingState:
//		droneExplode.Advance();
//		if (droneExplode.AnimEnd())
//		{
//			state = DeadState;
//		}
	}
}

void Drone::Draw(Graphics & gfx)
{
	switch (state)
	{
	case AliveState:
		droneAnim.Draw(int(pos.x), int(pos.y), gfx);
		break;
//	case DyingState:
//		droneExplode.Draw(int(pos.x), int(pos.y), gfx);
//		break;
	}
}

RectF Drone::GetCollisionRect() const
{
	return RectF(pos, width, height);
}

void Drone::Reset()
{
	state = AliveState;
	pos.x = resetX;
	pos.y = -40.0f;
	droneAnim.Reset();
}

void Drone::HandleCollision()
{
	state = DyingState;
}

int Drone::GetCollisionDmg() const
{
	return collisionDmg;
}

bool Drone::IsAlive() const
{
	return state == AliveState;
}


