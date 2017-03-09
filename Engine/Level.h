#pragma once

#include "BlackHoleManager.h"
#include "DroneManager.h"
#include "EnergyBoostManager.h"
#include "MineManager.h"
#include "ObstacleManager.h"
#include "ShieldManager.h"
#include "SmallEnemyManager.h"
#include "BigEnemyManager.h"
#include <fstream>

class Level
{
public:
	Level(BlackHoleManager& BHM, DroneManager& DroneM, EnergyBoostManager& EBoostM, MineManager& MineM, ObstacleManager& ObstacleM, ShieldManager& ShieldM,
		SmallEnemyManager& SmallEnemyM, BigEnemyManager& bBigEnemyM);
	void ReadLevel();
	
private:
	static constexpr int width = 16;
	static constexpr int height = 20;
	static constexpr int cellWidth = 50;
	static constexpr int cellHeight = -60;
	int level[height][width];
	std::ifstream read;
	BlackHoleManager& bHoleM;
	DroneManager& droneM;
	EnergyBoostManager& eBoostM;
	MineManager& mineM;
	ObstacleManager& obstacleM;
	ShieldManager& shieldM;
	SmallEnemyManager& smallEnemyM;
	BigEnemyManager& bigEnemyM;
};