#include "Level.h"

Level::Level(BlackHoleManager & BHM, DroneManager& DroneM)
	:
	bHoleM(BHM),
	droneM(DroneM)
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
			}
		}
	}
}
