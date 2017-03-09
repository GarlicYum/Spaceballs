#pragma once

#include "Drone.h"
#include <random>
#include <vector>

class DroneManager
{
public:
	DroneManager(AnimationFrames& DroneAnim, AnimationFrames& DroneExplode, Sound& ExploSound);
	void Draw(Graphics& gfx);
	void Reset();
	void Update(float dt);
	int GetDroneCount() const;
	Drone& GetDrone(int Idx);
	const Drone& GetDrone(int Idx) const;
	void SpawnDrone(float X, float Y);

private:
	int nDrones = 0;
	std::vector<Drone> drone;
	AnimationFrames& droneAnim;
	Sound& exploSound;
	AnimationFrames& droneExplode;
};