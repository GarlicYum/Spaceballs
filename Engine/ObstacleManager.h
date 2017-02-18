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
	void SpawnObstacle(float dt);
	int GetObstacleCount() const;
	Obstacle& GetObstacle(int Idx);
	const Obstacle& GetObstacle(int Idx) const;
	void Reset();

private:
	static constexpr int nObstaclesMax = 4;
	int nObstacles = 0;
	static constexpr float newObstacle = 9.0f;
	float obstacleCounter = 0.0f;
	std::vector<Obstacle> obstacle;
};