/****************************************************************************************** 
 *	Chili DirectX Framework Version 12.04.24											  *	
 *	Game.h																				  *
 *	Copyright 2012 PlanetChili.net														  *
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
#include "Mouse.h"
#include "Sound.h"

#define NPOO 25
#define GOALRAD 12

class Game
{
public:
	Game( HWND hWnd,const KeyboardServer& kServer,const MouseServer& mServer );
	void Go();
private:
	void ComposeFrame();
	/********************************/
	/*  User Functions              */

	void DrawFace( int x,int y );
	void DrawPoo( int x,int y );
	void DrawGameOver( int x,int y );
	void UpdateFace();
	void UpdatePoo();
	void ResetGoal();

	/********************************/
private:
	D3DGraphics gfx;
	KeyboardClient kbd;
	MouseClient mouse;
	DSound audio;
	/********************************/
	/*  User Variables              */
	int nPoo;
	bool gameIsOver;

	int faceX;
	int faceY;
	int goalX;
	int goalY;

	float pooX[ NPOO ];
	float pooY[ NPOO ];
	float pooXVelocity[ NPOO ];
	float pooYVelocity[ NPOO ];

	Sound fart;
	Sound tinkle;

	/********************************/
};