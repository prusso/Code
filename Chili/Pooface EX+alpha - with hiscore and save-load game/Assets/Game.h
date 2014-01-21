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
#include "Mouse.h"
#include "Sound.h"

#define NPOO 25
#define GOALRAD 25
#define NSCORES 10
#define TIMEBUFLEN 20
#define MAXPOOSPEED 4.0f
#define MINAPPEARDIST 30.0f
#define FACESPEED 7
#define WORLDHEIGHT 1199
#define WORLDWIDTH 1599
// resolution of background grid
#define GRIDRESOLUTION 50
// camera tracking offset vertical/horizontal
// is the offset from the edge off the screen 
// to the camera tracking rectangle
#define CTRKOFFVERT 180
#define CTRKOFFHOR 240

class Game
{
private:
	struct HighScore
	{
		int score;
		char time[TIMEBUFLEN];
	};

	struct Poo
	{
		float x;
		float y;
		float vx;
		float vy;
	};

public:
	Game( HWND hWnd,const KeyboardServer& kServer,const MouseServer& mServer );
	~Game();
	void Go();
private:
	void ComposeFrame();
	/********************************/
	/*  User Functions              */

	void DrawFaceClipped( int x,int y );
	void DrawPooClipped( int x,int y );
	void DrawPooUnclipped( int x,int y );
	void DrawGameOver( int x,int y );
	// unlike drawface and drawpoo, drawbackground works
	// in world space instead of screen space, so it needs
	// the camera coordinates
	void DrawBackgroundClipped( int cameraX,int cameraY );
	void UpdateFace();
	void UpdatePoo();
	void UpdateCamera();
	void RandomizePooVelocity( int index );
	void RandomizePooPosition( int index );
	void ResetGame();
	void ResetGoal();

	void ClearScoreboard();
	void InsertScore(HighScore score);
	void SaveScore();
	HighScore GetScore();
	void LoadScore();

	void SaveGame();
	void LoadGame();
	/********************************/
private:
	D3DGraphics gfx;
	KeyboardClient kbd;
	MouseClient mouse;
	DSound audio;
	/********************************/
	/*  User Variables              */
	int nPoo;
	int nGoal;
	bool gameIsOver;

	int faceX;
	int faceY;
	int goalX;
	int goalY;
	int cameraX;
	int cameraY;

	Poo poo[ NPOO ];

	HighScore scores[NSCORES];

	Sound fart;
	Sound ting;
	/********************************/
};