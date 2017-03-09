#include "Level.h"

Level::Level(BlackHoleManager & BHM, DroneManager& DroneM, EnergyBoostManager& EBoostM, MineManager& MineM, ObstacleManager& ObstacleM)
	:
	bHoleM(BHM),
	droneM(DroneM),
	eBoostM(EBoostM),
	mineM(MineM),
	obstacleM(ObstacleM)
{}

void Level::ReadLevel()
{
	read.open("level.txt");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			read >> level[i][j];
		}
	}
	read.close();

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			switch (level[i][j])
			{
			case 1:
				bHoleM.SpawnBlackHole(float(j * cellDimension), float(-i * cellDimension));
				break;

			case 2:
				droneM.SpawnDrone(float(j * cellDimension), float(-i * cellDimension));
				break;

			case 3:
				eBoostM.SpawnEnergyBoost(float(j * cellDimension), float(-i * cellDimension));
				break;

			case 4:
				mineM.SpawnMine(float(j * cellDimension), float(-i * cellDimension));
				break;

			case 5:
				obstacleM.SpawnObstacle(float(j * cellDimension), float(-i * cellDimension));
				break;
			}
		}
	}
}
