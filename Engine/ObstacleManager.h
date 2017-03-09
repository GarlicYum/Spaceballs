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
	void SpawnObstacle(float X, float Y);
	int GetObstacleCount() const;
	Obstacle& GetObstacle(int Idx);
	const Obstacle& GetObstacle(int Idx) const;
	void Reset();

private:
	int nObstacles = 0;
	std::vector<Obstacle> obstacle;
	const Surface& surface;
};