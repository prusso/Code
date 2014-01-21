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

class Game
{
public:
	Game( HWND hWnd,const KeyboardServer& kServer );
	void Go();

private:
	enum XOState
	{
		EMPTY,
		X,
		O
	};

private:
	void ComposeFrame();
	/********************************/
	/*  User Functions              */

	void DrawGrid( int x, int y );
	void DrawX( int x, int y);
	void DrawO( int x, int y);
	void DrawCursor( int x, int y );
	void DrawOWins( int x, int y );
	void DrawTie( int x, int y );
	void DrawXWins( int x, int y);
	void DrawGameOver( int x, int y);
	void DrawAgain( int x, int y);
	void DrawEndScreen( int x, int y, XOState state );

	void SetSquareState( int index, XOState state );
	XOState GetSquareState( int index );
	void SetSquareState( int ix, int iy, XOState state );
	XOState GetSquareState( int ix, int iy );
	
	void DoUserInput();
	void EndTurn();
	XOState CheckForVictory();

	void AIGetNextMoveRand();
	void DoAITurnRand();
	void AICheckSq();

	/********************************/
private:
	D3DGraphics gfx;
	KeyboardClient kbd;
	/********************************/
	/*  User Variables              */
	
	//int x;
	//int y;
	
	XOState s0;
	XOState s1;
	XOState s2;
	XOState s3;
	XOState s4;
	XOState s5;
	XOState s6;
	XOState s7;
	XOState s8;
	int cursorX;
	int cursorY;
	bool keysPressedLastFrame;
	XOState activePlayer;
	int nTurns;


	int AIMoveX;
	int AIMoveY;

	/********************************/
};