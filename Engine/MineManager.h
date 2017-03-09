#pragma once
#include "Mine.h"
#include <random>
#include <vector>

class MineManager
{
public:
	MineManager(Sound& Explosion, const Surface& MineSurface, AnimationFrames& ExplosionFrames);
	void Update(float Dt);
	void Draw(Graphics& gfx);
	void SpawnMine(float X, float Y);
	Mine& GetMine(int Idx);
	const Mine& GetMine(int Idx) const;
	int GetMineCount() const;
	void Reset();

private:
	int nMines = 0;
	std::vector<Mine> mine;
	const Surface& mineSurface;
	AnimationFrames& exploFrames;
	Sound& explosion;
};

