#include "DroneManager.h"

DroneManager::DroneManager(AnimationFrames & DroneAnim, AnimationFrames& DroneExplode, Sound& ExploSound)
{
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist(40.0f, 750.0f);

	for (int i = 0; i < nDronesMax; ++i)
	{
		drone.emplace_back<Drone>(Drone{ 250.0f, DroneAnim, DroneExplode, ExploSound });
	}
}

void DroneManager::Draw(Graphics & gfx)
{
	for (int i = 0; i < nDrones; ++i)
	{
		drone[i].Draw(gfx);
	}
}

void DroneManager::Reset()
{
	nDrones = 0;
	droneCounter = 0.0f;
	for (int i = 0; i < nDronesMax; ++i)
	{
		drone[i].Reset();
	}
}

void DroneManager::Update(float dt)
{
	if ((droneCounter += dt) >= newDrone && (nDrones != nDronesMax))
	{
		nDrones++;
		droneCounter = 0.0f;
	}
	for (int i = 0; i < nDrones; ++i)
	{
		drone[i].Update(dt);
	}
}

int DroneManager::GetDroneCount() const
{
	return nDrones;
}

Drone & DroneManager::GetDrone(int Idx)
{
	return drone[Idx];
}

const Drone & DroneManager::GetDrone(int Idx) const
{
	return drone[Idx];
}
