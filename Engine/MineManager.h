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
	void SpawnMine();
	Mine& GetMine(int Idx);
	const Mine& GetMine(int Idx) const;
	int GetMineCount() const;
	void Reset();

private:
	static constexpr int nMinesMax = 100;
	int nMines = 0;
	int mineCounter = 0;
	int newMine = 30;
	std::vector<Mine> mine;
};

