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
		star[i].x = xDist(rng);
		star[i].y = yDist(rng);
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
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		ship.y -= 5;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		ship.y += 5;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		ship.x -= 5;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		ship.x += 5;
	}

	/*
	NOTES TO SELF
	1. make the bullets finish going off screen even if player let's go of space bar
	2. Make it so a fired bullet doesn't follow the ships x position
	*/

	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		ship.Shoot(gfx);
	}
	

	ship.ClampScreen(gfx);
	
	for (int i = 0; i < nStars; i++)
	{
		if (star[i].y + 3 >= gfx.ScreenHeight)
		{
			star[i].y = 2;
		}
		else
		{
			star[i].y++;
		}
	}	
}

void Game::ComposeFrame()
{
	for (int i = 0; i < nStars; i++)
	{
		star[i].Draw(gfx);
	}
	
	ship.Draw(gfx);
}
