#include "MainWindow.h"
#include "Ship.h"
#include "Surface.h"

Ship::Ship(BulletManager& Manager, Surface& ShipSurface, 
	Surface& red, AnimationFrames& shiprekt, AnimationFrames& holeAnim, 
	AnimationFrames& holeRektAnim, AnimationFrames& shipexplo, AnimationFrames& exhaustAnim, 
	AnimationFrames& rektExhaustAnim, Sound& shipexplodesound, Sound& blackholesound, AnimationFrames& bulletAnim)
	:
	bManager(Manager),
	shipSurface(ShipSurface),
	redSurface(red), 
	shipRekt(shiprekt, 2),
	blackHole(holeAnim, 1),
	blackHoleRekt(holeRektAnim, 1),
	shipExplo(shipexplo, 2),
	exhaust(exhaustAnim, 2),
	rektExhaust(rektExhaustAnim, 2),
	shipExplodeSound(shipexplodesound),
	blackHoleSound(blackholesound),
	bulletSprite(bulletAnim, 2)
{}

void Ship::HandleCollision(int Damage)
{
	switch (state)
	{
	case BlackHoleTransitionState:
		if (health.GetHealthAmount() > lowHealth)
		{
			blackHole.Advance();
		}
		else
		{
			blackHoleRekt.Advance();
		}

		if ((blackHole.AnimEnd() || blackHoleRekt.AnimEnd()) && firstTransition)
		{
			blackHoleRekt.Reset();
			blackHole.Reset();
			oldX = pos.x;
			oldY = pos.y;
			pos.x = 350.0f;
			pos.y = 500.0f;
			state = BlackHoleState;
			firstTransition = false;
		}
		else if (blackHole.AnimEnd() || blackHoleRekt.AnimEnd())
		{
			blackHoleRekt.Reset();
			blackHole.Reset();
			pos.x = oldX;
			pos.y = oldY;
			firstTransition = true;
			state = TransitionBackState;
		}
		///////////////what happens in update and draw during transitionback? let world know about it
		break;

	case AliveState:
		health.Damage(Damage);
		isHit = true;
		break;

	case BlackHoleState:
		health.Damage(Damage);
		isHit = true;
		break;
	}	
}

void Ship::Draw(Graphics& gfx)
{
	switch (state)
	{
	case AliveState:
		if (health.GetHealthAmount() > lowHealth)
		{
			if (!isMoving)
			{
				gfx.DrawSpriteKey(int(pos.x), int(pos.y), shipSurface, shipSurface.GetPixel(0, 0));
			}
			
			else
			{
				exhaust.Draw(int(pos.x), int(pos.y), gfx);
			}
		}

		else
		{
			if (!isMoving)
			{
				shipRekt.Draw(int(pos.x), int(pos.y), gfx);
			}

			else
			{
				rektExhaust.Draw(int(pos.x), int(pos.y), gfx);
			}
		}

		if (isHit)
		{
			gfx.DrawSpriteKey(int(pos.x), int(pos.y), redSurface, redSurface.GetPixel(0, 0));
		}
		break;

	case BlackHoleTransitionState:
		if (health.GetHealthAmount() > lowHealth)
		{
			blackHole.Draw(int(pos.x), int(pos.y), gfx);
		}

		else
		{
			blackHoleRekt.Draw(int(pos.x), int(pos.y), gfx);
		}
		break;

	case TransitionBackState:
		if (health.GetHealthAmount() > lowHealth)
		{
			blackHole.Draw(int(pos.x), int(pos.y), gfx);
		}

		else
		{
			blackHoleRekt.Draw(int(pos.x), int(pos.y), gfx);
		}
		break;

	case ExplodingState:
		shipExplo.Draw(int(pos.x) - exploX, int(pos.y) - exploY, gfx);
		break;

	case BlackHoleState:
		if (health.GetHealthAmount() > lowHealth)
		{
			exhaust.Draw(int(pos.x), int(pos.y), gfx);
		}

		else
		{
			rektExhaust.Draw(int(pos.x), int(pos.y), gfx);
		}

		if (isHit)
		{
			gfx.DrawSpriteKey(int(pos.x), int(pos.y), redSurface, redSurface.GetPixel(0, 0));
		}
		break;
	}	

	health.Draw(gfx);
	bManager.DrawBullets(gfx, bulletSprite);
}

void Ship::ClampScreen()
{
	pos.x = std::max(0.f, std::min(pos.x, float(Graphics::ScreenWidth) - (width + 1.f)));
	pos.y = std::max(0.f, std::min(pos.y, float(Graphics::ScreenHeight) - (height + 1.f)));
}

void Ship::PlayerInput(Keyboard& kbd, float dt)
{
	if (state == AliveState)
	{
		if (kbd.KeyIsPressed(VK_UP))
		{
			pos.y -= speed * dt;
			isMoving = true;
		}

		else if (kbd.KeyIsPressed(VK_DOWN))
		{
			pos.y += speed * dt;
			isMoving = false;
		}

		else
		{
			isMoving = false;
		}

		if (kbd.KeyIsPressed(VK_LEFT))
		{
			pos.x -= speed * dt;
		}

		else if (kbd.KeyIsPressed(VK_RIGHT))
		{
			pos.x += speed * dt;
		}

		if (kbd.KeyIsPressed(VK_SPACE))
		{
			bManager.FireBullet(Vec2(pos.x + canonX, pos.y + canonY));
		}

		else
		{
			bManager.ResetShotsFired();
		}
	}

	else if (state == BlackHoleState)
	{
		if (kbd.KeyIsPressed(VK_LEFT))
		{
			pos.x -= speed * dt;
		}

		else if (kbd.KeyIsPressed(VK_RIGHT))
		{
			pos.x += speed * dt;
		}
	}
}

void Ship::Restore(int restore)
{
	health.Restore(restore);
}

bool Ship::IsAlive() const
{
	return state == AliveState;
}

bool Ship::IsDead() const
{
	return state == DeadState;
}

bool Ship::IsBlackHole() const
{
	return state == BlackHoleState;
}

bool Ship::ExitingBlackHole() const
{
	return state == TransitionBackState;
}

RectF Ship::GetCollisionRect()
{
	return RectF(pos, width, height);
}

float Ship::GetX() const
{
	return pos.x;
}

float Ship::GetWidth() const
{
	return width;
}

float Ship::GetY() const
{
	return pos.y;
}

float Ship::GetHeight() const
{
	return height;
}

int Ship::GetHealth() const
{
	return health.GetHealthAmount();
}

void Ship::SethitTarget(bool hit)
{
	hitTarget = hit;
}

void Ship::AddGravity(Vec2 & gravity)
{
	pos -= gravity;
}

void Ship::SetY(float Y)
{
	pos.y = Y;
}

void Ship::SetX(float X)
{
	pos.x = X;
}

int Ship::GetDmg() const
{
	return dmg;
}

void Ship::CollidesWithHole(bool collides)
{
	if (collides && (state == AliveState || state == BlackHoleState))
	{
		blackHoleSound.Play(0.8f, 1.0f);
		state = BlackHoleTransitionState;
	}	
}

void Ship::Reset()
{
	pos.x = 300.0f;
	pos.y = 300.0f;
	health.Reset();
	isHit = false;
	blackHole.Reset();
	blackHoleRekt.Reset();
	shipExplo.Reset();
	state = AliveState;
}

void Ship::Update(Keyboard & wnd, float dt)
{
	switch (state)
	{
	case AliveState:
		bManager.UpdateBullets(dt, bulletSprite);
		if (int(pos.y) > (Graphics::ScreenHeight - 10))
		{
			health.Damage(health.GetHealthAmount());
		}

		if (isHit)
		{
			isHitCounter++;
			if (isHitCounter >= 10)
			{
				isHitCounter = 0;
				isHit = false;
			}
		}

		if (health.GetHealthAmount() <= lowHealth)
		{
			if (!isMoving)
			{
				shipRekt.Advance();
				if (shipRekt.AnimEnd())
				{
					shipRekt.Reset();
				}
			}
			else
			{
				rektExhaust.Advance();
				if (rektExhaust.AnimEnd())
				{
					rektExhaust.Reset();
				}
			}
		}

		else if (isMoving)
		{
			exhaust.Advance();
			if (exhaust.AnimEnd())
			{
				exhaust.Reset();
			}
		}

		if (!health.HasHealth())
		{
			shipExplodeSound.Play();
			state = ExplodingState;
		}
		break;

	case ExplodingState:
		shipExplo.Advance();
		if (shipExplo.AnimEnd())
		{
			state = DeadState;
		}
		break;

	case BlackHoleState:
		pos.y -= (speed / 30.0f) * dt;

		if (isHit)
		{
			isHitCounter++;
			if (isHitCounter >= 10)
			{
				isHitCounter = 0;
				isHit = false;
			}
		}

		if (!health.HasHealth())
		{
			shipExplodeSound.Play();
			state = ExplodingState;
		}

		else if (health.GetHealthAmount() <= lowHealth)
		{
			rektExhaust.Advance();
			if (rektExhaust.AnimEnd())
			{
				rektExhaust.Reset();
			}
		}

		else if (health.GetHealthAmount() > lowHealth)
		{
			exhaust.Advance();
			if (exhaust.AnimEnd())
			{
				exhaust.Reset();
			}
		}
		break;

	case TransitionBackState:
		if (health.GetHealthAmount() > lowHealth)
		{
			blackHole.Reverse();
		}
		else
		{
			blackHoleRekt.Reverse();
		}

		if (blackHole.AnimEnd() || blackHoleRekt.AnimEnd())
		{
			blackHoleRekt.Reset();
			blackHole.Reset();
			state = AliveState;
		}
		break; 

	}
	PlayerInput(wnd, dt);
	ClampScreen();
}
