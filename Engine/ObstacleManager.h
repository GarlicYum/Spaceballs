#pragma once

#include "Obstacle.h"
#include <vector>
#include <random>

class ObstacleManager
{
public:
	ObstacleManager(const Surface& obstacleSurface);
	void Draw(Graphics& gfx);
	void Update(float dt);
	void SpawnObstacle();
	int GetObstacleCount() const;
	Obstacle& GetObstacle(int Idx);
	const Obstacle& GetObstacle(int Idx) const;
	void Reset();

private:
	static constexpr int nObstaclesMax = 4;
	int nObstacles = 0;
	int newObstacle = 550;
	int obstacleCounter = 0;
	std::vector<Obstacle> obstacle;
};