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

#define DUDEWIDTH 50
#define DUDEHEIGHT 80
#define DUDENFRAMES 14
#define DUDEFRAMETIME (60 / DUDENFRAMES)
#define DUDEKEYCOLOR D3DCOLOR_XRGB(255,255,255)
#define DUDEFILENAME "WalkinDude\\wdude"
#define DUDESPEED 1.55f
#define NDUDES 60

class Game
{
public:
	struct AnimatedSpriteTemplate
	{
		Sprite* frames;
		 int nFrames;
		 int frameDuration;
	};
	struct AnimatedSpriteInstance
	{
		AnimatedSpriteTemplate* templat;
		int currentFrame;
		int currentFrameExposure;
		float x,y;
	};

public:
	Game( HWND hWnd,const KeyboardServer& kServer,const MouseServer& mServer );
	
	void LoadAnimatedSprite( AnimatedSpriteTemplate* templat, Sprite* sprites, D3DCOLOR* surfaces,
		const char* basename, int width, int height, D3DCOLOR key, int nFrames, int frameDuration );

	void CreateSpriteInstance( AnimatedSpriteTemplate* templat, AnimatedSpriteInstance* instance );
	void UpdateAnimation(AnimatedSpriteInstance* instance);
	void DrawSpriteInstance(AnimatedSpriteInstance* instance);
	void Go();
private:
	void ComposeFrame();
	/********************************/
	/*  User Functions              */

	/********************************/
private:
	D3DGraphics gfx;
	KeyboardClient kbd;
	MouseClient mouse;
	DSound audio;
	/********************************/
	/*  User Variables              */
	D3DCOLOR dudeSurfaces[DUDEHEIGHT * DUDEWIDTH * DUDENFRAMES];
	Sprite dudeSprites[DUDENFRAMES];
	AnimatedSpriteTemplate dudeTemplate;

	AnimatedSpriteInstance dudes[NDUDES];

	/********************************/
};