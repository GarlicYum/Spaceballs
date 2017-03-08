#include "World.h"

World::World()
	:
	droneM(droneAnim, droneExplo, droneExploSound),
	bigEnemyExplo(L"bigshipexplo\\", 16),
	bigEnemy(350.0f, bigEnemySurface, bigEnemyBulletM, bigEnemyExplo, bigEnemyExploSound, bigBulletAnim),
	bulletAnim(L"bullet\\", 18),
	bigBulletAnim(L"bigbullet\\", 26),
	smallBulletAnim(L"smallbullet\\", 18),
	bossAnim(L"boss\\", 8),
	boss(bossAnim, bossLeftBulletM, bossRightBulletM, bossCenterBulletM, bigBulletAnim, lightBallAnim,
		bossExplo, bossPreExplo, shipExplodeSound),
	lightBallAnim(L"lightball\\", 28),
	animExplosion(L"mineExplo\\", 8),
	ship(bulletM, shipSurface, redSurface, shipRekt, shipHoleAnim, shipHoleRektAnim, shipExploAnim, 
		shipExhaustAnim, rektExhaustAnim, shipExplodeSound, blackHoleSound, bulletAnim),
	mineM(explosion, mine, animExplosion),
	eBoostM(eBoostSound, eBoostHeart),
	obstacleM(obstacleSurface),
	shipRekt(L"shiprekt\\", 16),
	bHoleAnim(L"blackhole\\", 40),
	blackholeM(bHoleAnim),
	shipHoleAnim(L"shiphole\\", 28),
	shipHoleRektAnim(L"shipholerekt\\", 28),
	shipExploAnim(L"shipexplo\\", 29),
	smallEnemyM(smallEnemyExhaust, smallEnemyExplode, smallExplo, smallLeftBulletM, smallRightBulletM, smallBulletAnim),
	shipExhaustAnim(L"shipexhaust\\", 4),
	rektExhaustAnim(L"rektexhaust\\", 16),
	smallEnemyExhaust(L"smallenemyexhaust\\", 8),
	smallEnemyExplode(L"smallshipexplo\\", 13),
	blackHoleLevel(BlackHoleBGFrames, cometAnim),
	BlackHoleBGFrames(L"blackholeBG\\", 20),
	cometAnim(L"comet\\", 6),
	droneAnim(L"drone\\", 8),
	droneExplo(L"dronexplo\\", 8),
	bossExplo(L"bossexplo\\", 85),
	bossPreExplo(L"bosspreexplo\\", 15),
	levelTimer(108.0f)
	
{
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist(0.0f, 790.0f);
	std::uniform_real_distribution<float> yDist(0.0f, 590.0f);
	for (int i = 0; i < nStars; ++i)
	{
		star[i].Spawn(Vec2(xDist(rng), yDist(rng)), 3.0f);
	}
	for (int i = 0; i < nBigStars; ++i)
	{
		starB[i].Spawn(Vec2(xDist(rng), yDist(rng)), 6.0f);
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
		if (levelTimer.Pause(Dt))
		{
			bossSong.Play(1.0f, 0.5f);
			gState = BossState;
		}
		titleSong.StopAll();
		ship.Update(Kbd, Dt);
		UpdateStars(Dt);
		blackholeM.Update(Dt);
		mineM.Update(Dt);
		eBoostM.Update(ship, Dt);
		shieldM.Update(ship, Dt, shieldon, shieldoff);
		obstacleM.Update(Dt);
		CheckCollisions(Dt);
		smallEnemyM.Update(Dt, ship.GetX());
		droneM.Update(Dt);
		bigEnemy.Update(Dt);

		if (!ship.IsAlive())
		{
			mainSong.StopAll();

			if (ship.IsDead())
			{
				gameOverSong.Play(1.0f, 0.5f);
				gState = GameOverState;
			}
		}

		if (ship.IsBlackHole())
		{
			mainSong.StopAll();
			gState = BlackHoleState;

			if (ship.IsDead())
			{
				gameOverSong.Play(1.0f, 0.5f);
				gState = GameOverState;
			}
		}
		break;

	case BlackHoleState:
		ship.Update(Kbd, Dt);
		blackHoleLevel.Update(Dt);
		CheckCollisions(Dt);
		if (ship.ExitingBlackHole())
		{
			gState = TransitionState;
		}
		if (ship.IsDead())
		{
			gState = GameOverState;
		}
		break;

	case TransitionState:
		ship.Update(Kbd, Dt);
		if (ship.IsAlive())
		{
			gState = PlayState;
			mainSong.Play(1.0f, 0.5f);
		}
		blackHoleLevel.Reset();
		break;

	case BossState:
		titleSong.StopAll();
		ship.Update(Kbd, Dt);
		UpdateStars(Dt);
		boss.Update(Dt, ship.GetX());
		CheckCollisions(Dt);

		if (boss.IsEntering())
		{
			ship.PrepareForBoss(Dt);
		}

		if (boss.IsAliveState())
		{
			ship.EnableInput();
			if (!starsSpedUp)
			{
				SpeedUpStars(3.0f);
				starsSpedUp = true;
			}
		}

		if (!ship.IsAlive())
		{
			bossSong.StopAll();
		}
		if (ship.IsDead())
		{
			gameOverSong.Play(1.0f, 0.5f);
			gState = GameOverState;
		}
		if (boss.IsExploding())
		{
			bossSong.StopAll();
			ship.PrepareForBoss(Dt);
			ResetStarSpeed();
		}
		if (boss.IsDead())
		{
			if (ship.FlyOffScreen(Dt))
			{
				gState = CreditState;
				creditSong.Play(1.0f, 0.5f);
			}
		}
		break;

	case GameOverState:
		PlayerInput(Kbd);
		break;

	case CreditState:
		PlayerInput(Kbd);
		UpdateStars(Dt);
		if (creditY > -1400)
		{
			creditY -= creditSpeed * Dt;
		}
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
		blackholeM.Draw(Gfx);
		eBoostM.Draw(Gfx, ship);
		shieldM.Draw(Gfx);
		ship.Draw(Gfx);
		mineM.Draw(Gfx);
		obstacleM.Draw(Gfx);
		smallEnemyM.Draw(Gfx);
		droneM.Draw(Gfx);
		bigEnemy.Draw(Gfx);
		break;
	case BlackHoleState:
		blackHoleLevel.Draw(Gfx);
		ship.Draw(Gfx);
		break;
	case TransitionState:
		DrawStars(Gfx);
		blackholeM.Draw(Gfx);
		eBoostM.Draw(Gfx, ship);
		shieldM.Draw(Gfx);
		ship.Draw(Gfx);
		mineM.Draw(Gfx);
		obstacleM.Draw(Gfx);
		smallEnemyM.Draw(Gfx);
		break;
	case BossState:
		DrawStars(Gfx);
		ship.Draw(Gfx);
		boss.Draw(Gfx);
		break;
	case GameOverState:
		Gfx.DrawSprite(0, 0, gameOverSurface);
		break;
	case CreditState:
		DrawStars(Gfx);
		Gfx.DrawSpriteAlpha(0, int(creditY), creditSurface);
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

void World::SpeedUpStars(float factor)
{
	for (int i = 0; i < nBigStars; ++i)
	{
		starB[i].SpeedUp(factor);
	}
	for (int i = 0; i < nStars; ++i)
	{
		star[i].SpeedUp(factor);
	}
}

void World::ResetStarSpeed()
{
	for (int i = 0; i < nBigStars; ++i)
	{
		starB[i].ResetSpeed();
	}
	for (int i = 0; i < nStars; ++i)
	{
		star[i].ResetSpeed();
	}
}

void World::PlayerInput(Keyboard& Kbd)
{
	switch (gState)
	{
	case TitleState:

		while (!Kbd.KeyIsEmpty())
		{
			event = Kbd.ReadKey();
			if (event.IsPress())
			{
				if (event.GetCode() == VK_RETURN)
				{
					gState = PlayState; //////////////////////////////////////////////////////////////////////////temporary, normally PlayState
					mainSong.Play(1.0f, 0.5f);
				//	bossSong.Play(1.0f, 0.5f);
				}
			}
		}
		
		break;
	case GameOverState:
		
		while (!Kbd.KeyIsEmpty())
		{
			event = Kbd.ReadKey();
			if (event.IsPress())
			{
				if (event.GetCode() == VK_RETURN)
				{
					ship.Reset();
					mineM.Reset();
					shieldM.Reset();
					obstacleM.Reset();
					eBoostM.Reset();
					bulletM.Reset();
					smallLeftBulletM.Reset();
					smallRightBulletM.Reset();
					blackholeM.Reset();
					smallEnemyM.Reset();
					droneM.Reset();
					bigEnemy.Reset();
					bigEnemyBulletM.Reset();
					bossLeftBulletM.Reset();
					bossRightBulletM.Reset();
					bossCenterBulletM.Reset();
					boss.Reset();
					levelTimer.Reset();
					ResetStarSpeed();
					creditY = 800;
					starsSpedUp = false;
					gameOverSong.StopAll();
					titleSong.Play();
					gState = TitleState;
				}
			}
		}
		
		break;

	case CreditState:
		while (!Kbd.KeyIsEmpty())
		{
			event = Kbd.ReadKey();
			if (event.IsPress())
			{
				if (event.GetCode() == VK_RETURN)
				{
					ship.Reset();
					mineM.Reset();
					shieldM.Reset();
					obstacleM.Reset();
					eBoostM.Reset();
					bulletM.Reset();
					smallLeftBulletM.Reset();
					smallRightBulletM.Reset();
					blackholeM.Reset();
					smallEnemyM.Reset();
					droneM.Reset();
					bigEnemy.Reset();
					bigEnemyBulletM.Reset();
					bossLeftBulletM.Reset();
					bossRightBulletM.Reset();
					bossCenterBulletM.Reset();
					boss.Reset();
					ResetStarSpeed();
					creditY = 800;
					starsSpedUp = false;
					creditSong.StopAll();
					titleSong.Play();
					gState = TitleState;
				}
			}
		}

		break;
	}
}

void World::CheckCollisions(float dt)
{
	const auto shipRect = ship.GetCollisionRect();
	const auto& blackholeRect = blackHoleLevel.GetCollisionRect();
	auto& shield = shieldM.GetShield();
	switch (gState)
	{
	case PlayState:
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
					shield.HandleCollision(mine.GetDamageCost());
				}
			}
			else if (IsColliding(shipRect, mineRect) && ship.IsAlive())
			{
				mine.HandleCollision(ship.GetDmg());
				ship.HandleCollision(mine.GetDamageCost(), dt);
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

		for (int i = 0; i < smallEnemyM.GetSmallCount(); ++i)
		{
			auto& smallShip = smallEnemyM.GetSmallShip(i);
			if (!smallShip.IsAlive())
				continue;
			const auto smallShipRect = smallShip.GetCollisionRect();

			if (IsColliding(shipRect, smallShipRect) && !smallShip.GetCoolDown() && ship.IsAlive())
			{
				shipCollideSound.Play(1.1f, 0.9f);
				smallShip.HandleCollision(0);
				ship.HandleCollision(smallShip.GetCollisionDmg(), dt);
			}

			for (int i = 0; i < bulletM.GetNumBullets(); ++i)
			{
				auto& bullet = bulletM.GetBullet(i);
				if (!bullet.IsActive())
					continue;
				const auto bulletRect = bullet.GetCollisionRect();
				if (IsColliding(bulletRect, smallShipRect))
				{
					smallShip.HandleCollision(bullet.GetDamage());
					bullet.HandleCollision();
					break;
				}
			}

			for (int i = 0; i < smallLeftBulletM.GetNumBullets(); ++i)
			{
				auto& bulletLeft = smallLeftBulletM.GetBullet(i);
				if (!bulletLeft.IsActive())
					continue;
				const auto bulletLeftRect = bulletLeft.GetCollisionRect();

				if (shield.GetisActive())
				{
					const auto shieldRect = shield.GetCollisionRect();
					if (IsColliding(shieldRect, bulletLeftRect))
					{
						bulletLeft.HandleCollision();
						shield.HandleCollision(bulletLeft.GetDamage());
					}
				}

				else if (IsColliding(bulletLeftRect, shipRect))
				{
					ship.HandleCollision(bulletLeft.GetDamage(), dt);
					bulletLeft.HandleCollision();
					break;
				}
			}

			for (int i = 0; i < smallRightBulletM.GetNumBullets(); ++i)
			{
				auto& bulletRight = smallRightBulletM.GetBullet(i);
				if (!bulletRight.IsActive())
					continue;
				const auto bulletRightRect = bulletRight.GetCollisionRect();

				if (shield.GetisActive())
				{
					const auto shieldRect = shield.GetCollisionRect();
					if (IsColliding(shieldRect, bulletRightRect))
					{
						bulletRight.HandleCollision();
						shield.HandleCollision(bulletRight.GetDamage());
					}
				}

				else if (IsColliding(bulletRightRect, shipRect))
				{
					ship.HandleCollision(bulletRight.GetDamage(), dt);
					bulletRight.HandleCollision();
					break;
				}
			}
		}

		for (int i = 0; i < blackholeM.GetBlackHoleCount(); ++i)
		{
			auto& blackhole = blackholeM.GetBlackHole(i);
			const auto blackHoleRect = blackhole.GetCollisionRect();

			if (IsColliding(shipRect, blackHoleRect) && blackhole.GetIsActive())
			{
				Vec2 gravity = shipRect.GetCenter() - blackHoleRect.GetCenter();

				if (gravity.GetLengthSq() < 5.0f)
				{
					blackhole.StopVy();
					ship.CollidesWithHole(true);
					ship.HandleCollision(ship.GetHealth(), dt);

					if (ship.IsBlackHole())
					{
						blackhole.StartVy();
						blackhole.Deactivate();
					}
				}

				else if (blackholeM.GetBlackHole(i).GetIsActive())
				{
					gravity.Normalize();
					gravity *= 210.0f;
					ship.AddGravity(gravity, dt);
				}
			}
		}

		for (int i = 0; i < obstacleM.GetObstacleCount(); ++i)
		{
			auto& obstacle = obstacleM.GetObstacle(i);
			const auto& obstacleBottomRect = obstacle.GetBottomCollisionRect();
			const auto& obstacleTopRect = obstacle.GetTopCollisionRect();
			const auto& obstacleLeftRect = obstacle.GetLeftCollisionRect();
			const auto& obstacleRightRect = obstacle.GetRightCollisionRect();

			if (IsColliding(shipRect, obstacleBottomRect))
			{
				obstacle.HandleBottomCollision(ship);
			}

			else if (IsColliding(shipRect, obstacleTopRect))
			{
				obstacle.HandleTopCollision(ship);
			}

			else if (IsColliding(shipRect, obstacleLeftRect))
			{
				obstacle.HandleLeftCollision(ship);
			}

			else if (IsColliding(shipRect, obstacleRightRect))
			{
				obstacle.HandleRightCollision(ship);
			}

			for (int i = 0; i < bulletM.GetNumBullets(); ++i)
			{
				auto& bullet = bulletM.GetBullet(i);
				if (!bullet.IsActive())
					continue;
				const auto bulletRect = bullet.GetCollisionRect();

				if (IsColliding(bulletRect, obstacleBottomRect))
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

		for (int i = 0; i < droneM.GetDroneCount(); ++i)
		{
			auto& drone = droneM.GetDrone(i);
			if (!drone.IsAlive())
				continue;
			const auto droneRect = drone.GetCollisionRect();

			if (shield.GetisActive())
			{
				const auto shieldRect = shield.GetCollisionRect();
				if (IsColliding(shieldRect, droneRect))
				{
					drone.HandleCollision();
					shield.HandleCollision(drone.GetCollisionDmg());
				}
			}
			else if (IsColliding(shipRect, droneRect) && ship.IsAlive())
			{
				drone.HandleCollision();
				ship.HandleCollision(drone.GetCollisionDmg(), dt);
			}

			for (int i = 0; i < bulletM.GetNumBullets(); ++i)
			{
				auto& bullet = bulletM.GetBullet(i);
				if (!bullet.IsActive())
					continue;
				const auto bulletRect = bullet.GetCollisionRect();
				if (IsColliding(bulletRect, droneRect))
				{
					drone.HandleCollision();
					bullet.HandleCollision();
					break;
				}
			}
		}

		const auto bigShipRect = bigEnemy.GetCollisionRect();
		if (bigEnemy.IsAlive())
		{
			if (IsColliding(shipRect, bigShipRect) && ship.IsAlive())
			{
				shipCollideSound.Play(1.1f, 0.9f);
				bigEnemy.HandleCollision(0);
				ship.HandleCollision(bigEnemy.GetCollisionDmg(), dt);
			}

			for (int i = 0; i < bulletM.GetNumBullets(); ++i)
			{
				auto& bullet = bulletM.GetBullet(i);
				if (!bullet.IsActive())
					continue;
				const auto bulletRect = bullet.GetCollisionRect();
				if (IsColliding(bulletRect, bigShipRect))
				{
					bigEnemy.HandleCollision(bullet.GetDamage());
					bullet.HandleCollision();
					break;
				}
			}

			for (int i = 0; i < bigEnemyBulletM.GetNumBullets(); ++i)
			{
				auto& bullet = bigEnemyBulletM.GetBullet(i);
				if (!bullet.IsActive())
					continue;
				const auto bulletRect = bullet.GetCollisionRect();

				if (shield.GetisActive())
				{
					const auto shieldRect = shield.GetCollisionRect();
					if (IsColliding(shieldRect, bulletRect))
					{
						bullet.HandleCollision();
						shield.HandleCollision(bullet.GetDamage());
					}
				}

				else if (IsColliding(bulletRect, shipRect))
				{
					ship.HandleCollision(bullet.GetDamage(), dt);
					bullet.HandleCollision();
					break;
				}
			}
		}
		break;
		
		case BlackHoleState:
			if (IsColliding(blackholeRect, shipRect))
			{
				ship.CollidesWithHole(true);
				ship.HandleCollision(0, dt);
			}

			for (int i = 0; i < blackHoleLevel.GetCometCount(); ++i)
			{
				auto& comet = blackHoleLevel.GetComet(i);
				if (!comet.IsActive())
					continue;
				const auto cometRect = comet.GetCollisionRect();
				if (IsColliding(shipRect, cometRect))
				{
					comet.HandleCollision();
					ship.HandleCollision(comet.GetDmg(), dt);
				}
			}
		break;

		case BossState:

			if (boss.IsAliveState())
			{
				const auto& bossBottomRect = boss.GetBottomCollisionRect();
				const auto& bossTopRect = boss.GetTopCollisionRect();
				const auto& bossLeftRect = boss.GetLeftCollisionRect();
				const auto& bossRightRect = boss.GetRightCollisionRect();
				const auto& bossRect = boss.GetCollisionRect();
				if (IsColliding(bossBottomRect, shipRect) && ship.IsAlive())
				{
					ship.SetY(boss.GetBottom());

					if (!boss.GetCoolDown())
					{
						ship.HandleCollision(boss.GetCollisionDmg(), dt);
						boss.HandleCollision(0);
						shipCollideSound.Play(1.1f, 0.9f);
					}
				}

				else if (IsColliding(bossLeftRect, shipRect) && ship.IsAlive())
				{
					ship.SetX(boss.GetLeft() - ship.GetWidth());

					if (!boss.GetCoolDown())
					{
						ship.HandleCollision(boss.GetCollisionDmg(), dt);
						boss.HandleCollision(0);
						shipCollideSound.Play(1.1f, 0.9f);
					}
				}

				else if (IsColliding(bossRightRect, shipRect) && ship.IsAlive())
				{
					ship.SetX(boss.GetRight());

					if (!boss.GetCoolDown())
					{
						ship.HandleCollision(boss.GetCollisionDmg(), dt);
						boss.HandleCollision(0);
						shipCollideSound.Play(1.1f, 0.9f);
					}
				}

				else if (IsColliding(bossTopRect, shipRect) && ship.IsAlive())
				{
					ship.SetY(boss.GetTop() - ship.GetHeight());

					if (!boss.GetCoolDown())
					{
						ship.HandleCollision(boss.GetCollisionDmg(), dt);
						boss.HandleCollision(0);
						shipCollideSound.Play(1.1f, 0.9f);
					}
				}

				for (int i = 0; i < bulletM.GetNumBullets(); ++i)
				{
					auto& bullet = bulletM.GetBullet(i);
					if (!bullet.IsActive())
						continue;
					const auto bulletRect = bullet.GetCollisionRect();
					if (IsColliding(bulletRect, bossRect))
					{
						bullet.HandleCollision();
						boss.HandleCollision(bullet.GetBossDmg());
						break;
					}
				}

				for (int i = 0; i < bossLeftBulletM.GetNumBullets(); ++i)
				{
					auto& leftBullet = bossLeftBulletM.GetBullet(i);
					if (!leftBullet.IsActive())
						continue;
					const auto leftBulletRect = leftBullet.GetCollisionRect();
					if (IsColliding(leftBulletRect, shipRect))
					{
						leftBullet.HandleCollision();
						ship.HandleCollision(leftBullet.GetDamage(), dt);
						break;
					}
				}

				for (int i = 0; i < bossRightBulletM.GetNumBullets(); ++i)
				{
					auto& rightBullet = bossRightBulletM.GetBullet(i);
					if (!rightBullet.IsActive())
						continue;
					const auto rightBulletRect = rightBullet.GetCollisionRect();
					if (IsColliding(rightBulletRect, shipRect))
					{
						rightBullet.HandleCollision();
						ship.HandleCollision(rightBullet.GetDamage(), dt);
						break;
					}
				}

				for (int i = 0; i < bossCenterBulletM.GetNumBullets(); ++i)
				{
					auto& centerBullet = bossCenterBulletM.GetBullet(i);
					if (!centerBullet.IsActive())
						continue;
					const auto centerBulletRect = centerBullet.GetCollisionRect();
					if (IsColliding(centerBulletRect, shipRect))
					{
						centerBullet.HandleCollision();
						ship.HandleCollision(centerBullet.GetDamage(), dt);
						break;
					}
				}
			}
			break;
	}
}