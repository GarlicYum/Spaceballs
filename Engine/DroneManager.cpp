#include "DroneManager.h"

DroneManager::DroneManager(AnimationFrames & DroneAnim, AnimationFrames& DroneExplode, Sound& ExploSound)
	:
	droneAnim(DroneAnim),
	exploSound(ExploSound),
	droneExplode(DroneExplode)
{}

void DroneManager::Draw(Graphics & gfx)
{
	for (int i = 0; i < nDrones; ++i)
	{
		drone[i].Draw(gfx);
	}
}

void DroneManager::Reset()
{
	for (int i = 0; i < nDrones; ++i)
	{
	//	drone[i].Reset();
		drone.pop_back();
	}
	nDrones = 0;
}

void DroneManager::Update(float dt)
{
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

void DroneManager::SpawnDrone(float X, float Y)
{
	nDrones++;
	drone.emplace_back<Drone>(Drone{ X, Y, droneAnim, droneExplode, exploSound });
}
