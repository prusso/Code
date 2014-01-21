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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

Game::Game( HWND hWnd,const KeyboardServer& kServer,const MouseServer& mServer )
:	gfx( hWnd ),
	audio( hWnd ),
	kbd( kServer ),
	mouse( mServer ),
	timeMin(FLT_MAX),
	timeMax(0),
	timeSum(0.0f),
	lastMin(0.0f),
	lastMax(0.0f),
	lastAvg(0.0f),
	frameCount(0)
{
	srand ( time(NULL) );

	LoadAnimatedSprite( &dudeTemplate, DUDEFILENAME, DUDEWIDTH, DUDEHEIGHT, DUDEKEYCOLOR, DUDENFRAMES, DUDEFRAMETIME);
	
	for ( int index = 0; index < NDUDES; index++)
	{
		CreateSpriteInstance( &dudeTemplate, &dudes[index]);
		dudes[index].x = rand() % (800 - dudeTemplate.frames[0].width);
		dudes[index].y = rand() % (600 - dudeTemplate.frames[0].height);
		dudes[index].currentFrame = rand() % dudeTemplate.nFrames;
	}
	LoadFont( &fixedSys, fontSurf, "Fixedsys16x28.bmp", 16, 28, 32);

	LoadSprite(&backgroundSprite,"background.bmp", 800, 600, D3DCOLOR_XRGB(255,0,255) );

}

Game::~Game()
{
	FreeSprite(&backgroundSprite);
	FreeAnimatedSprite( &dudeTemplate );
}

void Game::LoadAnimatedSprite( AnimatedSpriteTemplate* templat, 
		const char* basename, int width, int height, D3DCOLOR key, int nFrames, int frameDuration)
{
	templat->frames = (Sprite*)malloc(sizeof(Sprite) * nFrames );

	for (int index = 0; index < nFrames; index++ )
	{
		char fileNameBuffer[64];
		sprintf(fileNameBuffer, "%s%.2d.bmp", basename, index);
		LoadSprite( &templat->frames[index], fileNameBuffer, width, height, key );
	}

	templat->nFrames = nFrames;
	templat->frameDuration = frameDuration;
}

void Game::FreeAnimatedSprite( AnimatedSpriteTemplate* templat )
{
	for (int index = 0; index < templat->nFrames; index++ )
	{
		FreeSprite( &templat->frames[index] );
	}

	free(templat->frames);
}

void Game::CreateSpriteInstance( AnimatedSpriteTemplate* templat, AnimatedSpriteInstance* instance )
{
	instance->templat = templat;
	instance->currentFrameExposure = 0;
	instance->currentFrame = 0;
	instance->x = 0.0f;
	instance->y = 0.0f;
}

	void Game::UpdateAnimation(AnimatedSpriteInstance* instance)
	{
		instance->currentFrameExposure++;
		if (instance->currentFrameExposure >= instance->templat->frameDuration)
		{
			instance->currentFrame++;
			instance->currentFrame %= instance->templat->nFrames;
			instance->currentFrameExposure = 0;
		}
	}
	
	void Game::DrawSpriteInstance(AnimatedSpriteInstance* instance)
	{
		gfx.DrawSprite( (int)instance->x,(int)instance->y,&instance->templat->frames[instance->currentFrame] );
	}

void Game::Go()
{
	for (int index = 0; index < NDUDES; index++)
	{

		dudes[index].x += DUDESPEED;
		if (dudes[index].x + DUDEWIDTH >= 799 )
		{
			dudes[index].x = 0;
		}
		UpdateAnimation( &dudes[index] );
	}


	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::ComposeFrame()
{
	gfx.DrawSprite(0, 0, &backgroundSprite);

	timer.StartWatch();
	for (int index = 0; index < NDUDES; index++)
	{
		DrawSpriteInstance( &dudes[index] );
	}
	timer.StopWatch();

	const float frameTime = timer.GetTimeMilli();
	timeSum += frameTime;
	timeMin = min( lastMin, frameTime );
	timeMax = max( timeMax, frameTime );
	frameCount++;
	if (frameCount >= 60)
	{
		lastAvg = timeSum / 60.0f;
		lastMin = timeMin;
		lastMax = timeMax;
		timeSum = 0.0f;
		timeMin = FLT_MAX;
		timeMax = 0.0f;
		frameCount = 0;
	}

	char buffer[64];
	sprintf(buffer, "# of sprites: %d | Average render time: %.2f", NDUDES, lastAvg );
	gfx.DrawString(buffer,0,0,&fixedSys,D3DCOLOR_XRGB(255,0,0) );
	sprintf(buffer, "Min render time: %.2f | Max render time: %.2f", lastMin, lastMax );
	gfx.DrawString(buffer,0,28,&fixedSys,D3DCOLOR_XRGB(255,0,0) );

	/*
	if ( mouse.IsInWindow() )
	{
		// draw each char individually
		gfx.DrawChar( 'P', 0 + mouse.GetMouseX(), 0 + mouse.GetMouseY(), &fixedSys, D3DCOLOR_XRGB(0, 255, 0) );
		gfx.DrawChar( 'U', 16 + mouse.GetMouseX(), 0 + mouse.GetMouseY(), &fixedSys, D3DCOLOR_XRGB(255, 255, 0) );
		gfx.DrawChar( 'B', 32 + mouse.GetMouseX(), 0 + mouse.GetMouseY(), &fixedSys, D3DCOLOR_XRGB(0, 255, 255) );
		gfx.DrawChar( 'E', 48 + mouse.GetMouseX(), 0 + mouse.GetMouseY(), &fixedSys, D3DCOLOR_XRGB(255, 255, 0) );
		gfx.DrawChar( 'S', 64 + mouse.GetMouseX(), 0 + mouse.GetMouseY(), &fixedSys, D3DCOLOR_XRGB(0, 0, 255) );
		gfx.DrawChar( '!', 80 + mouse.GetMouseX(), 0 + mouse.GetMouseY(), &fixedSys, D3DCOLOR_XRGB(255, 0, 0) );
		

		// draw whole string of characters
		gfx.DrawString( "Pubes!", 0 + mouse.GetMouseX(), 0 + mouse.GetMouseY(), &fixedSys, D3DCOLOR_XRGB(255, 0, 0) );
		
		}
*/

}