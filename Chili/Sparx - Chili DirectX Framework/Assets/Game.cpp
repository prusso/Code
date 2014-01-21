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
#include <stdlib.h>
#include <time.h>


Game::Game( HWND hWnd,const KeyboardServer& kServer )
:	gfx ( hWnd ),
	kbd( kServer ),
	x(400),
	y(300),
	dx(7),
	dy(7),
	speed(6),
	r(255),
	g(255),
	b(255),
	score(1)
{}

void Game::Go()
{
	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::draw_reticle(int x, int y, int r, int g, int b)
{
	gfx.PutPixel(     x,      y, 255, 255, 255);
	gfx.PutPixel(     x - 1,  y, 255, 255, 255);
	gfx.PutPixel(     x + 1,  y, 255, 255, 255);
	gfx.PutPixel(     x,      y - 1, 255, 255, 255);
	gfx.PutPixel(     x,      y + 1, 255, 255, 255);
	gfx.PutPixel(-5 + x,      y, r, g, b);
	gfx.PutPixel(-4 + x,      y, r, g, b);
	gfx.PutPixel(-3 + x,      y, r, g, b);
	gfx.PutPixel( 3 + x,      y, r, g, b);
	gfx.PutPixel( 4 + x,      y, r, g, b);
	gfx.PutPixel( 5 + x,      y, r, g, b);
	gfx.PutPixel(	  x, -5 + y, r, g, b);
	gfx.PutPixel(     x, -4 + y, r, g, b);
	gfx.PutPixel(     x, -3 + y, r, g, b);
	gfx.PutPixel(     x,  3 + y, r, g, b);
	gfx.PutPixel(     x,  4 + y, r, g, b);
	gfx.PutPixel(     x,  5 + y, r, g, b);
}

void Game::draw_dude(int dx, int dy)
{
	for (int i = 0; i < 5; i++)
	{
	gfx.PutPixel(     dx,      dy, 255, 255, 255);
	gfx.PutPixel(     dx - i,  dy, 255, 255, 255);
	gfx.PutPixel(     dx + i,  dy, 255, 255, 255);
	gfx.PutPixel(     dx,      dy - i, 255, 255, 255);
	gfx.PutPixel(     dx,      dy + i, 255, 255, 255);
	gfx.PutPixel(     dx - i,  dy + i, 255, 255, 255);
	gfx.PutPixel(     dx + i,  dy - i, 255, 255, 255);
	gfx.PutPixel(     dx - i,  dy - i, 255, 255, 255);
	gfx.PutPixel(     dx + i,  dy + i, 255, 255, 255);
	}
}

void Game::ComposeFrame()
{
	
	// reset crosshair colors to white on every tick
	r = 255;
	g = 255;
	b = 255;

	// keyboard controls to move the crosshair
	if (kbd.RightIsPressed())
	{
		x += speed;
	}
	if (kbd.LeftIsPressed())
	{
		x -= speed;
	}
	if (kbd.UpIsPressed() && y > speed)
	{
		y -= speed;
	}
	if (kbd.DownIsPressed() && y < 600 - speed)
	{
		y += speed;
	}
	// fire (changes crosshair color) or some other action
	if (kbd.SpaceIsPressed())
	{
		r = 0;
	}
	// defines size of "target" box in center of screen
	if (x > 300 && x < 500 && y > 200 && y < 400)
	{
		g = 0;
		b = 0;
	}
	
	// draw crosshairs
draw_reticle(x, y, r, g, b);

	// draw dude
draw_dude(dx, dy);

	// "randomly" move dude based on time
	dx += rand()%5;
	srand (time (NULL));
	dy += rand()%4;
	srand (time (NULL));
	dy -= rand()%3;
	// enabling more "entropy" causes inacurracy in shooting dude and movement breakage :(
	//srand (time (NULL));
	//dx -= rand()%6;

	// don't let dude go off the y axis on the console screen
	if (dy < 15)
	{
		dy = 15;
	}

	if (dy > 584) 
	{
		dy = 584;
	}

	// target dude within n pixels and press spacebar to "kill"/reset his position 
	if ((x - dx) < 4 && (y - dy) < 4 && kbd.SpaceIsPressed())
	{

		for (int i = 0; i < 15; i++)
		{
		gfx.PutPixel(     dx,      dy, 255, 255, 255);
		gfx.PutPixel(     dx - i,  dy, 255, 255, 255);
		gfx.PutPixel(     dx + i,  dy, 255, 255, 255);
		gfx.PutPixel(     dx,      dy - i, 255, 255, 255);
		gfx.PutPixel(     dx,      dy + i, 255, 255, 255);
		gfx.PutPixel(     dx - i,  dy + i, 255, 255, 255);
		gfx.PutPixel(     dx + i,  dy - i, 255, 255, 255);
		gfx.PutPixel(     dx - i,  dy - i, 255, 255, 255);
		gfx.PutPixel(     dx + i,  dy + i, 255, 255, 255);
		}

		// increment your score
		score++;

		// reset dude
		dx = -5;
		dy = 5;
	}
	
}