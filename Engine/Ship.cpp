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
	shipRekt(shiprekt, 2.0f),
	blackHole(holeAnim, 1.0f),
	blackHoleRekt(holeRektAnim, 1.0f),
	shipExplo(shipexplo, 2.0f),
	exhaust(exhaustAnim, 2.0f),
	rektExhaust(rektExhaustAnim, 2.0f),
	shipExplodeSound(shipexplodesound),
	blackHoleSound(blackholesound),
	bulletSprite(bulletAnim, 2.0f)
{}

void Ship::HandleCollision(int Damage, float dt)
{
	switch (state)
	{
	case BlackHoleTransitionState:
		if (health.GetHealthAmount() > lowHealth)
		{
			blackHole.Advance(dt);
		}
		else
		{
			blackHoleRekt.Advance(dt);
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
				gfx.DrawSpriteAlpha(int(pos.x), int(pos.y), shipSurface);
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
			gfx.DrawSpriteAlpha(int(pos.x), int(pos.y), redSurface);
		}
		bManager.DrawBullets(gfx, bulletSprite);
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
		bManager.DrawBullets(gfx, bulletSprite);
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
			gfx.DrawSpriteAlpha(int(pos.x), int(pos.y), redSurface);
		}
		break;
	}	

	health.Draw(gfx);
}

void Ship::ClampScreen()
{
	if (!gameComplete)
	{
		pos.x = std::max(0.f, std::min(pos.x, float(Graphics::ScreenWidth) - (width + 1.f)));
		pos.y = std::max(0.f, std::min(pos.y, float(Graphics::ScreenHeight) - (height + 1.f)));
	}
}

void Ship::PlayerInput(Keyboard& kbd, float dt)
{
	if (inputEnabled)
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

void Ship::EnableInput()
{
	inputEnabled = true;
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

void Ship::AddGravity(Vec2 & gravity, float dt)
{
	pos -= gravity * dt;
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

void Ship::PrepareForBoss(float dt)
{
	inputEnabled = false;
	const RectF rect = GetCollisionRect();
	Vec2 resetPos = Vec2(400.0f, 500.0f);
	Vec2 diff = rect.GetCenter() - resetPos;

	if (diff.GetLengthSq() > 5.0f)
	{
		diff.Normalize();
		diff *= 210.0f;
		pos -= diff * dt;
	}
}

float Ship::GetRight() const
{
	return pos.x + width;
}

float Ship::GetBottom() const
{
	return pos.y + height;
}

bool Ship::FlyOffScreen(float dt)
{
	gameComplete = true;
	if ((pos.y + height) > -20.0f)
	{
		isMoving = true;
		pos.y -= speed * dt;
		return false;
	}
	else
		return true;
}

void Ship::Reset()
{
	isMoving = false;
	pos.x = 300.0f;
	pos.y = 300.0f;
	health.Reset();
	isHit = false;
	isHitCounter = 0.0f;
	blackHole.Reset();
	blackHoleRekt.Reset();
	shipExplo.Reset();
	state = AliveState;
	gameComplete = false;
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
			if ((isHitCounter += dt) >= hitOver)
			{
				isHitCounter = 0.0f;
				isHit = false;
			}
		}

		if (health.GetHealthAmount() <= lowHealth)
		{
			if (!isMoving)
			{
				shipRekt.Advance(dt);
				if (shipRekt.AnimEnd())
				{
					shipRekt.Reset();
				}
			}
			else
			{
				rektExhaust.Advance(dt);
				if (rektExhaust.AnimEnd())
				{
					rektExhaust.Reset();
				}
			}
		}

		else if (isMoving)
		{
			exhaust.Advance(dt);
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
		bManager.UpdateBullets(dt, bulletSprite);
		shipExplo.Advance(dt);
		if (shipExplo.AnimEnd())
		{
			state = DeadState;
		}
		break;

	case BlackHoleState:
		pos.y -= (speed / 30.0f) * dt;

		if (isHit)
		{
			if ((isHitCounter += dt) >= hitOver)
			{
				isHitCounter = 0.0f;
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
			rektExhaust.Advance(dt);
			if (rektExhaust.AnimEnd())
			{
				rektExhaust.Reset();
			}
		}

		else if (health.GetHealthAmount() > lowHealth)
		{
			exhaust.Advance(dt);
			if (exhaust.AnimEnd())
			{
				exhaust.Reset();
			}
		}
		break;

	case TransitionBackState:
		if (health.GetHealthAmount() > lowHealth)
		{
			blackHole.Reverse(dt);
		}
		else
		{
			blackHoleRekt.Reverse(dt);
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
