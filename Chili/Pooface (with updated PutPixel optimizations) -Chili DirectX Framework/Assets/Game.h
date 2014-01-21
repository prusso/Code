/****************************************************************************************** 
 *	Chili DirectX Framework Version 11.12.17											  *	
 *	Game.h																				  *
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
#pragma once

#include "D3DGraphics.h"
#include "Keyboard.h"

#define NPOO 1000

struct Point
{
	int x;
	int y;
};

Point Midpoint(Point p1, Point p2);


class Game
{
	struct Poo
	{
		float x;
		float y;
	};

public:
	Game( HWND hWnd,const KeyboardServer& kServer );
	void Go();
private:
	void ComposeFrame();
	/********************************/
	/*  User Functions              */

	void DrawFace(int x, int y);
	void DrawPoo(int x, int y);
	void DrawGameOver(int x, int y);
	void UpdateFace();
	void UpdatePoo();

	/********************************/
private:
	D3DGraphics gfx;
	KeyboardClient kbd;
	/********************************/
	/*  User Variables              */

	int faceX;
	int faceY;
	
	bool allPooIsEaten;
	int nPoo;
	bool pooIsEaten[NPOO];

	Poo poo[NPOO];


	/********************************/
};