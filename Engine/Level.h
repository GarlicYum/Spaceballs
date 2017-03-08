#pragma once

#include "BlackHoleManager.h"
#include "DroneManager.h"
#include <fstream>

class Level
{
public:
	Level(BlackHoleManager& BHM, DroneManager& DroneM);
	void ReadLevel();
	
private:
	static constexpr int width = 20;
	static constexpr int height = 5;
	const int cellDimension = 40;
	int level[height][width];
	std::ifstream read;
	BlackHoleManager& bHoleM;
	DroneManager& droneM;
};