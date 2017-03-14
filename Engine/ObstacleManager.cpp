#include "ObstacleManager.h"

ObstacleManager::ObstacleManager(const Surface & obstacleSurface)
	:
	surface(obstacleSurface)
{}

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
	for (int i = 0; i < nObstacles; ++i)
	{
		obstacle.pop_back();
	//	obstacle[i].Reset();
	}
	nObstacles = 0;
}
