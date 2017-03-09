#include "ObstacleManager.h"

ObstacleManager::ObstacleManager(const Surface & obstacleSurface)
	:
	surface(obstacleSurface)
{
//	std::mt19937 rng;
//	std::uniform_real_distribution<float> xDist(0.0f, 545.0f);
//	for (int i = 0; i < nObstaclesMax; ++i)
//	{
//		obstacle.emplace_back<Obstacle>(Obstacle{ xDist(rng), obstacleSurface });
//	}
}

void ObstacleManager::Draw(Graphics & gfx)
{
	for (int i = 0; i < nObstacles; i++)
	{
		obstacle[i].Draw(gfx);
	}
}

void ObstacleManager::Update(float dt)
{
	for (int i = 0; i < nObstacles; ++i)
	{
		obstacle[i].Update(dt);
	}
}

void ObstacleManager::SpawnObstacle(float X, float Y)
{
//	if ((obstacleCounter += dt) > newObstacle && nObstacles != nObstaclesMax)
//	{
//		obstacleCounter = 0.0f;
//		nObstacles++;
//	}
	nObstacles++;
	obstacle.emplace_back<Obstacle>(Obstacle{ X, Y, surface });
}

int ObstacleManager::GetObstacleCount() const
{
	return nObstacles;
}

Obstacle & ObstacleManager::GetObstacle(int Idx)
{
	return obstacle[Idx];
}

const Obstacle & ObstacleManager::GetObstacle(int Idx) const
{
	return obstacle[Idx];
}

void ObstacleManager::Reset()
{
	nObstacles = 0;
//	obstacleCounter = 0;
//	for (int i = 0; i < nObstaclesMax; ++i)
//	{
//		obstacle[i].Reset();
//	}
}
