#pragma once

#include "Drone.h"
#include <random>
#include <vector>

class DroneManager
{
public:
	DroneManager(AnimationFrames& DroneAnim, AnimationFrames& DroneExplo, Sound& ExploSound);
	void Draw(Graphics& gfx);
	void Reset();
	void Update(float dt);
	int GetDroneCount() const;
	Drone& GetSmallShip(int Idx);
	const Drone& GetSmallShip(int Idx) const;

private:
	static constexpr int nDronesMax = 30;
	int nDrones = 0;
	float droneCounter = 0.0f;
	static constexpr float newDrone = 2.0f;
	std::vector<Drone> drone;
};