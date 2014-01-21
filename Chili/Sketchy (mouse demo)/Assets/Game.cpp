/****************************************************************************************** 
 *	Chili DirectX Framework Version 12.04.24											  *	
 *	Game.cpp																			  *
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
#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <malloc.h>

Game::Game( HWND hWnd,const KeyboardServer& kServer,const MouseServer& mServer )
:	gfx( hWnd ),
	kbd( kServer ),
	mouse( mServer ),
	canvasRed( NULL ),
	canvasBlue( NULL ),
	canvasGreen( NULL ),
	lastX( 0 ),
	lastY( 0 ),
	wasDrawingLast( false )
{
	// allocate heap memory for canvas
	canvasRed = (int*)malloc( sizeof( int ) * 800 * 600 );
	canvasGreen = (int*)malloc( sizeof( int ) * 800 * 600 );
	canvasBlue = (int*)malloc( sizeof( int ) * 800 * 600 );

	// clear canvas
	for( int y = 0; y < 600; y++ )
	{
		for( int x = 0; x < 800; x++ )
		{
			PutPixelCanvas( x,y,0,0,0 );
		}
	}
}

Game::~Game()
{
	// deallocate heap memory from canvas
	if( canvasRed )
	{
		free( canvasRed );
		canvasRed = NULL;
	}
	if( canvasGreen )
	{
		free( canvasGreen );
		canvasGreen = NULL;
	}
	if( canvasBlue )
	{
		free( canvasBlue );
		canvasBlue = NULL;
	}
}

void Game::PutPixelCanvas( int x,int y,int r,int g,int b )
{
	int index = x + 800*y;
	canvasRed[ index ] = r;
	canvasGreen[ index ] = g;
	canvasBlue[ index ] = b;
}

void Game::DrawLineCanvas( int x1,int y1,int x2,int y2,int r,int g,int blu )
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	if( dy == 0 && dx == 0 )
	{
		PutPixelCanvas( x1,y1,r,g,blu );
	}
	else if( abs( dy ) > abs( dx ) )
	{
		if( dy < 0 )
		{
			int temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		float m = (float)dx / (float)dy;
		float b = x1 - m*y1;
		for( int y = y1; y <= y2; y = y + 1 )
		{
			int x = (int)(m*y + b + 0.5f);
			PutPixelCanvas( x,y,r,g,blu );
		}
	}
	else
	{
		if( dx < 0 )
		{
			int temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		float m = (float)dy / (float)dx;
		float b = y1 - m*x1;
		for( int x = x1; x <= x2; x = x + 1 )
		{
			int y = (int)(m*x + b + 0.5f);
			PutPixelCanvas( x,y,r,g,blu );
		}
	}
}

void Game::Go()
{
	if( mouse.IsInWindow() )
	{
		if( mouse.LeftIsPressed() )
		{
			if( wasDrawingLast )
			{
				// draw white line from previous frame's cursor postion 
				// to current frame's cursor position
				DrawLineCanvas( lastX,lastY,
					mouse.GetMouseX(),mouse.GetMouseY(),
					255,255,255 );
			}
			lastX = mouse.GetMouseX();
			lastY = mouse.GetMouseY();
			wasDrawingLast = true;
		}
		else if( mouse.RightIsPressed() )
		{
			if( wasDrawingLast )
			{
				// draw red line from previous frame's cursor postion 
				// to current frame's cursor position
				DrawLineCanvas( lastX,lastY,
					mouse.GetMouseX(),mouse.GetMouseY(),
					255,0,0 );
			}
			lastX = mouse.GetMouseX();
			lastY = mouse.GetMouseY();
			wasDrawingLast = true;
		}
		else
		{
			wasDrawingLast = false;
		}
	}
	else
	{
		wasDrawingLast = false;
	}

	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::ComposeFrame()
{
	// copy canvas to framebuffer
	for( int y = 0; y < 600; y++ )
	{
		for( int x = 0; x < 800; x++ )
		{
			int index = x + 800*y;
			gfx.PutPixel( x,y,
				canvasRed[ index ],
				canvasGreen[ index ],
				canvasBlue[ index ] );
		}
	}
}