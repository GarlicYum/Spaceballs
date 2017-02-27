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

private:
	static constexpr int nDronesMax = 6;
	int nDrones = 0;
	float droneCounter = 0.0f;
	static constexpr float newDrone = 0.3f;
	std::vector<Drone> drone;
};