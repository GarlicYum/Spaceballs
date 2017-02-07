/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Ship.h"
#include "Star.h"
#include <random>
#include "Bullet.h"
#include "Sound.h"
#include "MineManager.h"
#include "FrameTimer.h"
#include "EnergyBoostManager.h"
#include "ShieldManager.h"
#include "TitleScreen.h"
#include "HighScore.h"
#include "Animation.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void UpdateStars(float dt);
	void DrawStars();
	void PlayerInput();
	void DrawLaser();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Ship ship;
	static constexpr int nStars = 100;
	Star star[nStars];
	static constexpr int nBigStars = 20;
	Star starB[nBigStars];
	Sound mainSong;
	Sound shieldon = L"shieldon.wav";
	Sound shieldoff = L"shieldoff.wav";
	Sound titleSong = L"War.wav";
	MineManager mineM;
	FrameTimer ft;
	EnergyBoostManager eBoostM;
	ShieldManager shieldM;
	bool gameIsStarted = false;
	TitleScreen title;
	bool songIsPlayed = false;
	static constexpr int nScores = 10;
	HighScore scores[nScores];
	Animation animation;
	Surface sprite;
	/********************************/
};