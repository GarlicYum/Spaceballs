#include "World.h"

World::World()
	:
	animExplosion(L"mineExplo\\", 8),
	ship(bulletM, shipSurface),
	mineM(explosion, mine, animExplosion),
	eBoostM(eBoostSound, eBoostHeart),
	obstacleM(obstacleSurface)
{
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist(0.0f, 790.0f);
	std::uniform_real_distribution<float> yDist(0.0f, 590.0f);
	for (int i = 0; i < nStars; ++i)
	{
		star[i].Spawn(xDist(rng), yDist(rng), 3.0f);
	}
	for (int i = 0; i < nBigStars; ++i)
	{
		starB[i].Spawn(xDist(rng), yDist(rng), 6.0f);
	}
}

World::~World()
{}

bool World::IsColliding(const RectF& A, const RectF& B)
{
	return A.Overlaps(B);
}

void World::Update(Keyboard& Kbd, float Dt)
{
	switch (gState)
	{
	case TitleState:
		if (!songIsPlayed)
		{
			titleSong.Play();
			songIsPlayed = true;
		}
		
		PlayerInput(Kbd);
		break;
	case PlayState:
		titleSong.StopAll();
		ship.Update(Kbd, Dt);
		bulletM.UpdateBullets(Dt);
		UpdateStars(Dt);
		mineM.Update(Dt);
		eBoostM.Update(ship, Dt);
		shieldM.Update(ship, Dt, shieldon, shieldoff);
		obstacleM.Update(Dt);

		CheckCollisions();
		if (!ship.HasHealth())
		{
			gState = GameOverState;
		}
		break;
	case GameOverState:
		gState = TitleState;
		break;
	}
}


void World::Draw(Graphics& Gfx)
{
	switch (gState)
	{
	case TitleState:
		title.Draw(Gfx);
		break;
	case PlayState:
		DrawStars(Gfx);
		shieldM.Draw(Gfx);
		mineM.Draw(Gfx);
		eBoostM.Draw(Gfx, ship);
		obstacleM.Draw(Gfx);
		ship.Draw(Gfx);
		break;
	}
}

void World::UpdateStars(float dt)
{
	for (int i = 0; i < nStars; ++i)
	{
		star[i].Update(dt);
	}

	for (int i = 0; i < nBigStars; ++i)
	{
		starB[i].Update(dt * 1.2f);
	}
}

void World::DrawStars(Graphics& Gfx)
{
	for (int i = 0; i < nStars; ++i)
	{
		star[i].Draw(Gfx);
	}

	for (int i = 0; i < nBigStars; ++i)
	{
		starB[i].DrawBig(Gfx);
	}
}

void World::PlayerInput(Keyboard& Kbd)
{
	if (Kbd.KeyIsPressed(VK_RETURN))
	{
		gState = PlayState;
		mainSong.Play(1.0f, 0.5f);
	}
}

void World::CheckCollisions()
{
	const auto shipRect = ship.GetCollisionRect();
	auto& shield = shieldM.GetShield();

	for (int i = 0; i < mineM.GetMineCount(); ++i)
	{
		auto& mine = mineM.GetMine(i);
		if (!mine.IsActive())
			continue;
		const auto mineRect = mine.GetCollisionRect();

		if (shield.GetisActive())
		{
			const auto shieldRect = shield.GetCollisionRect();
			if (IsColliding(shieldRect, mineRect))
			{
				mine.HandleCollision(shield.GetDmg());
			}
		}
		else if (IsColliding(shipRect, mineRect))
		{
			mine.HandleCollision(ship.GetDmg());
			ship.HandleCollision(mine.GetDamageCost());
		}

		for (int i = 0; i < bulletM.GetNumBullets(); ++i)
		{
			auto& bullet = bulletM.GetBullet(i);
			if (!bullet.IsActive())
				continue;
			const auto bulletRect = bullet.GetCollisionRect();
			if (IsColliding(bulletRect, mineRect))
			{
				mine.HandleCollision(bullet.GetDamage());
				bullet.HandleCollision();
				break;
			}
		}
	}

	for (int i = 0; i < obstacleM.GetObstacleCount(); ++i)
	{
		auto& obstacle = obstacleM.GetObstacle(i);
		const auto obstacleRect = obstacle.GetCollisionRect();

		if (IsColliding(shipRect, obstacleRect))
		{
			obstacle.HandleCollision(ship);
		}

		for (int i = 0; i < bulletM.GetNumBullets(); ++i)
		{
			auto& bullet = bulletM.GetBullet(i);
			if (!bullet.IsActive())
				continue;
			const auto bulletRect = bullet.GetCollisionRect();

			if (IsColliding(bulletRect, obstacleRect))
			{
				bullet.HandleCollision();
			}
		}
	}

	for (int i = 0; i < eBoostM.GetBoostCount(); ++i)
	{
		auto& boost = eBoostM.GetBoost(i);
		const auto boostRect = boost.GetCollisionRect();
		if (IsColliding(shipRect, boostRect))
		{
			boost.HandleCollision(ship);
		}
	}

	for (int i = 0; i < shieldM.GetShieldCount(); ++i)
	{
		auto& smallShield = shieldM.GetSmallShield(i);
		if (IsColliding(shipRect, smallShield.GetCollisionRect()))
		{
			smallShield.HandleCollision(shield);
		}
	}
}