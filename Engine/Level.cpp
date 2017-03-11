#include "Level.h"

Level::Level(BlackHoleManager & BHM, DroneManager& DroneM, EnergyBoostManager& EBoostM, MineManager& MineM, ObstacleManager& ObstacleM, ShieldManager& ShieldM,
	SmallEnemyManager& SmallEnemyM, BigEnemyManager& BigEnemyM, Boss& Boss)
	:
	bHoleM(BHM),
	droneM(DroneM),
	eBoostM(EBoostM),
	mineM(MineM),
	obstacleM(ObstacleM),
	shieldM(ShieldM),
	smallEnemyM(SmallEnemyM),
	bigEnemyM(BigEnemyM),
	boss(Boss)
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
				bHoleM.SpawnBlackHole(float(j * cellWidth), float(i * cellHeight));
				break;

			case 2:
				droneM.SpawnDrone(float(j * cellWidth), float(i * cellHeight));
				break;

			case 3:
				eBoostM.SpawnEnergyBoost(float(j * cellWidth), float(i * cellHeight));
				break;

			case 4:
				mineM.SpawnMine(float(j * cellWidth), float(i * cellHeight));
				break;

			case 5:
				obstacleM.SpawnObstacle(float(j * cellWidth), float(i * cellHeight));
				break;

			case 6:
				shieldM.SpawnShield(float(j * cellWidth), float(i * cellHeight));
				break;

			case 7:
				smallEnemyM.SpawnSmallShip(float(j * cellWidth), float(i * cellHeight));
				break;

			case 8:
				bigEnemyM.Spawn(float(j * cellWidth), float(i * cellHeight));
				break;

			case 9:
				boss.SetY(float(i * cellHeight));
				break;
			}
		}
	}
}
