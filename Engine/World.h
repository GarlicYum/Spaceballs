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
#include "SmallEnemyManager.h"
#include "BlackHoleLevel.h"
#include "DroneManager.h"
#include "BigEnemyShip.h"
#include "Boss.h"
#include "Timer.h"

class World
{
public:
	enum GameState
	{
		TitleState, PlayState, BlackHoleState, TransitionState, BossState, GameOverState, CreditState
	};
	World();
	~World();
	bool IsColliding(const RectF& A, const RectF& B);
	void Update(Keyboard& Kbd, float Dt);
	void Draw(Graphics &Gfx);

private:
	void UpdateStars(float dt);
	void PlayerInput(Keyboard& Kbd);
	void CheckCollisions(float dt);
	void DrawStars(Graphics& Gfx);
	void SpeedUpStars(float factor);
	void ResetStarSpeed();

private:
	Sound titleSong = L"War.mp3";
	TitleScreen title;
	
	Sound mainSong = L"actionnd.mp3";
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
	Surface redSurface = Surface::FromFile(L"shipred.png");
	AnimationFrames shipRekt;
	BulletManager bulletM;
	Ship ship;
	Sound shipExplodeSound = L"shipexplode.wav";

	Surface obstacleSurface = Surface::FromFile(L"obstacle.png");
	ObstacleManager obstacleM;

	Surface gameOverSurface = Surface::FromFile(L"gameover.png");
	Sound gameOverSong = L"64.mp3";

	AnimationFrames bHoleAnim;
	BlackHoleManager blackholeM;
	AnimationFrames shipHoleAnim;
	AnimationFrames shipHoleRektAnim;
	AnimationFrames shipExploAnim;
	AnimationFrames shipExhaustAnim;
	AnimationFrames rektExhaustAnim;
	Sound blackHoleSound = L"bhole.wav";

	static constexpr int nStars = 100;
	Star star[nStars];
	static constexpr int nBigStars = 20;
	Star starB[nBigStars];

	bool gameIsStarted = false;
	bool songIsPlayed = false;
	static constexpr int nScores = 10;
	HighScore scores[nScores];
	Keyboard::Event event;

	SmallEnemyManager smallEnemyM;
	AnimationFrames smallEnemyExhaust;
	AnimationFrames smallEnemyExplode;
	Sound smallExplo = L"smallshipexplo.wav";
	Sound shipCollideSound = L"shipcollide.wav";
	BulletManager smallLeftBulletM;
	BulletManager smallRightBulletM;

	AnimationFrames cometAnim;
	AnimationFrames BlackHoleBGFrames;
	BlackHoleLevel blackHoleLevel;

	AnimationFrames droneAnim;
	DroneManager droneM;
	AnimationFrames droneExplo;
	Sound droneExploSound = L"droneexplo.wav";

	Surface bigEnemySurface = Surface::FromFile(L"bigenemy.png");
	AnimationFrames bigEnemyExplo;
	BigEnemyShip bigEnemy;
	BulletManager bigEnemyBulletM;
	Sound bigEnemyExploSound = L"bigenemyexplo.wav";

	AnimationFrames bulletAnim;
	AnimationFrames bigBulletAnim;
	AnimationFrames smallBulletAnim;

	AnimationFrames bossAnim;
	Boss boss;
	BulletManager bossLeftBulletM;
	BulletManager bossRightBulletM;
	BulletManager bossCenterBulletM;
	Sound bossSong = L"bossmusic.mp3";
	AnimationFrames lightBallAnim;
	bool starsSpedUp = false;
	AnimationFrames bossExplo;
	AnimationFrames bossPreExplo;

	Surface creditSurface = Surface::FromFile(L"credit.png");
	float creditY = 800.0f;
	static constexpr float creditSpeed = 40.0f;
	Sound creditSong = L"credit.mp3";
	Timer levelTimer;
};