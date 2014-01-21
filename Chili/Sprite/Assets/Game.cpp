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

Game::Game( HWND hWnd,const KeyboardServer& kServer,const MouseServer& mServer )
:	gfx( hWnd ),
	audio( hWnd ),
	kbd( kServer ),
	mouse( mServer )
{
	srand ( time(NULL) );

	LoadAnimatedSprite( &dudeTemplate, dudeSprites, dudeSurfaces, DUDEFILENAME, DUDEWIDTH, DUDEHEIGHT, DUDEKEYCOLOR, DUDENFRAMES, DUDEFRAMETIME);
	
	for ( int index = 0; index < NDUDES; index++)
	{
		CreateSpriteInstance( &dudeTemplate, &dudes[index]);
		dudes[index].x = rand() % (800 - dudeTemplate.frames[0].width);
		dudes[index].y = rand() % (600 - dudeTemplate.frames[0].height);
		dudes[index].currentFrame = rand() % dudeTemplate.nFrames;
	}

}

void Game::LoadAnimatedSprite( AnimatedSpriteTemplate* templat, Sprite* sprites, D3DCOLOR* surfaces,
		const char* basename, int width, int height, D3DCOLOR key, int nFrames, int frameDuration)
{
	for (int index = 0; index < nFrames; index++ )
	{
		char fileNameBuffer[64];
		sprintf(fileNameBuffer, "%s%.2d.bmp", basename, index);
		LoadSprite( &sprites[index], &surfaces[DUDEWIDTH * DUDEHEIGHT * index], fileNameBuffer, width, height, key );
	}

	templat->frames = sprites;
	templat->nFrames = nFrames;
	templat->frameDuration = frameDuration;
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
	for (int index = 0; index < NDUDES; index++)
	{
		DrawSpriteInstance( &dudes[index] );
	}
}