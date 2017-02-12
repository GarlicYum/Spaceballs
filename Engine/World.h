#pragma once
#include "Animation.h"
#include "BulletManager.h"
#include "FrameTimer.h"
#include "EnergyBoostManager.h"
#include "Graphics.h"
#include "HighScore.h"
#include "Keyboard.h"
#include "MineManager.h"
#include "Mouse.h"
#include "ShieldManager.h"
#include "Ship.h"
#include "Sound.h"
#include "Star.h"
#include "TitleScreen.h"
#include "ObstacleManager.h"
#include "BlackHoleManager.h"

class World
{
public:
	enum GameState
	{
		TitleState, PlayState, GameOverState
	};
	World();
	~World();
	bool IsColliding(const RectF& A, const RectF& B);
	void Update(Keyboard& Kbd, float Dt);
	void Draw(Graphics &Gfx);

private:
	void UpdateStars(float dt);
	void PlayerInput(Keyboard& Kbd);
	void CheckCollisions();
	void DrawStars(Graphics& Gfx);

private:
	Sound titleSong = L"War.wav";
	TitleScreen title;
	
	Sound mainSong = L"actionnd.wav";
	Sound shieldon = L"shieldon.wav";
	Sound shieldoff = L"shieldoff.wav";
	ShieldManager shieldM;
	
	AnimationFrames animExplosion;
	Sound explosion = L"explo.wav";
	Surface mine = Surface::FromFile(L"mine.png");
	MineManager mineM;

	Sound eBoostSound = L"boost.wav";
	Surface eBoostHeart = Surface::FromFile(L"hart.png");
	EnergyBoostManager eBoostM;

	GameState gState = TitleState;

	Surface shipSurface = Surface::FromFile(L"shippit.png");
	Surface exhaustSurface = Surface::FromFile(L"shipper.png");
	Surface redSurface = Surface::FromFile(L"shipred.png");
	Surface rektSurface = Surface::FromFile(L"enginerekt.png");
	AnimationFrames shipRekt;
	BulletManager bulletM;
	Ship ship;

	Surface obstacleSurface = Surface::FromFile(L"obstacle.png");
	ObstacleManager obstacleM;

	Surface gameOverSurface = Surface::FromFile(L"gameover.png");
	Sound gameOverSong = L"64.wav";

	AnimationFrames bHoleAnim;
	BlackHoleManager blackholeM;

	static constexpr int nStars = 100;
	Star star[nStars];
	static constexpr int nBigStars = 20;
	Star starB[nBigStars];

	bool gameIsStarted = false;
	bool songIsPlayed = false;
	static constexpr int nScores = 10;
	HighScore scores[nScores];
	Keyboard::Event event;

};