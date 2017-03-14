#include "Drone.h"

Drone::Drone(float X, float Y, AnimationFrames & DroneAnim, AnimationFrames& DroneExplode, Sound& ExploSound)
	:
	pos(X, Y),
	resetPos(X, Y),
	droneAnim(DroneAnim, 2.0f),
	droneExplode(DroneExplode, 2.0f),
	exploSound(ExploSound)
{}

void Drone::Move(float dt)
{
	
	if (pos.y + height >= 0.0f)
	{
		pos.y += vel.y *dt;
		pos.x += vel.x *dt;
		if (pos.x >= resetPos.x)
		{
			vel.x -= 2.5f;
		}
		else
		{
			vel.x += 2.5f;
		}
	}
	else
	{
		pos.y += offScreenVel * dt;
	}
	
}

void Drone::Update(float dt)
{
	switch (state)
	{
	case AliveState:
		Move(dt);
		droneAnim.Advance(dt);
		if (droneAnim.AnimEnd())
		{
			droneAnim.Reset();
		}
		if (pos.y > Graphics::ScreenHeight)
		{
			state = DeadState;
		}
		break;

	case DyingState:
		droneExplode.Advance(dt);
		if (droneExplode.AnimEnd())
		{
			state = DeadState;
		}
		break;
	}
}

void Drone::Draw(Graphics & gfx)
{
	switch (state)
	{
	case AliveState:
		droneAnim.Draw(int(pos.x), int(pos.y), gfx);
		break;
	case DyingState:
		droneExplode.Draw(int(pos.x), int(pos.y), gfx);
		break;
	}
}

RectF Drone::GetCollisionRect() const
{
	return RectF(pos, width, height);
}

void Drone::HandleCollision()
{
	if (state == AliveState)
	{
		exploSound.Play(0.5f, 0.5f);
		state = DyingState;
	}
}

int Drone::GetCollisionDmg() const
{
	return collisionDmg;
}

bool Drone::IsAlive() const
{
	return state == AliveState;
}


