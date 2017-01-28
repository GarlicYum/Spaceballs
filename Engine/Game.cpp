/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist(0, 790);
	std::uniform_int_distribution<int> yDist(0, 590);
	for (int i = 0; i < nStars; i++)
	{
		star[i].Spawn(xDist(rng), yDist(rng), 3);
	}
	for (int i = 0; i < nBigStars; i++)
	{
		starB[i].Spawn(xDist(rng), yDist(rng), 6);
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	int vx = 0;
	int vy = 0;
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		vy -= 5;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		vy += 5;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		vx -= 5;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		vx += 5;
	}
	ship.SetVelocity(vx, vy);

	ship.FireBullet(wnd);
	ship.Update();
	UpdateStars();
}

void Game::UpdateStars()
{
	for (int i = 0; i < nStars; i++)
	{
		star[i].Update();
	}

	for (int i = 0; i < nBigStars; i++)
	{
		starB[i].Update();
	}
}

void Game::DrawStars()
{
	for (int i = 0; i < nStars; i++)
	{
		star[i].Draw(gfx);
	}
	for (int i = 0; i < nBigStars; i++)
	{
		starB[i].DrawBig(gfx);
	}
}

void Game::ComposeFrame()
{
	DrawStars();
	ship.Draw(gfx);
}
