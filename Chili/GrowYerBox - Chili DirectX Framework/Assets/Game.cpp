/****************************************************************************************** 
 *	Chili DirectX Framework Version 11.12.17											  *	
 *	Game.cpp																			  *
 *	Copyright 2011 PlanetChili.net														  *
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
#include "Game.h"

Game::Game( HWND hWnd,const KeyboardServer& kServer )
:	gfx ( hWnd ),
	kbd( kServer ),
	x100(350), y100(250),
	boxWidth(100), boxHeight(100)
{}

void Game::Go()
{
	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::ComposeFrame()
{
	int speed = 10;
	
				// keyboard controls to move the crosshair
	if (kbd.RightIsPressed())
	{
		x100 += speed;
	}
	if (kbd.LeftIsPressed())
	{
		x100 -= speed;
	}
	if (kbd.UpIsPressed())
	{
		y100 -= speed;
	}
	if (kbd.DownIsPressed())
	{
		y100 += speed;
	}
	if (kbd.SpaceIsPressed() && kbd.UpIsPressed())
	{
		boxHeight += 5;
		boxWidth += 5;
	}
	if (kbd.SpaceIsPressed() && kbd.DownIsPressed())
	{
		boxHeight -= 5;
		boxWidth -= 5;

	}
	
	
	// bound face to box
	if (x100 < 0)
	{
		x100 = 0;
	}

	if (x100 + boxWidth > 799)
	{
		x100 = 799 - boxWidth;
	}

	if (y100 < 0 )
	{
		y100 = 0;
	}

	if (y100 + boxHeight > 599)
	{
		y100 = 599 - boxHeight;
	}
	
	int y = y100;
	while (y < y100 + boxHeight)
	{
		int x = x100;
		while (x < x100 + boxWidth)
		{
			gfx.PutPixel(x,y,x,y,y);
			x++;
		}
		y++;
	}
}