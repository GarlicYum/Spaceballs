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

private:
	static constexpr int nObstaclesMax = 3;
	int nObstacles = 0;
	int newObstacle = 300;
	int obstacleCounter = 0;
	std::vector<Obstacle> obstacle;
};