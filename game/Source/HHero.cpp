#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "HHero.h"

namespace game_framework {
	HHero::HHero() {
		
	}
	void HHero::Initialize() {
		const int X_POS = 100;
		const int Y_POS = 600;
		x = X_POS;
		y = Y_POS;
		onMapX = 1;
		onMapY = 6;
		isMoving = false;
		stepCounter = 0;
		movingDirection = HERO_NOT_MOVING;
		faceDirection = 'r';
	}

	void HHero::LoadBitmap() {
		char imagePath[] = ".\\Bitmaps\\HERO\\0\\hero_x.bmp";
		for (int i = 0; i < 10; i++) {
			imagePath[22] = '0' + i;
			animation.AddBitmap(imagePath, RGB(0, 255, 0));
		}
		animation.AddBitmap(".\\Bitmaps\\HERO\\0\\hero_10.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\HERO\\0\\hero_11.bmp", RGB(0, 255, 0));
		
	}

	//void HHero::OnMove(bool mapEdge, int x, int y)
	//{
	//}

	void HHero::SetMovingDirection(char direction) {
		if (isMoving)
			return;

		isMoving = true;
		movingDirection = direction;
	}

	void HHero::SetXY(int nx, int ny) {
		x = nx; y = ny;
	}

	void HHero::SetHeroDirectionBitmap(char face) {
		if (face == HERO_FACING_RIGHT && faceDirection == HERO_FACING_LEFT) {
			faceDirection = HERO_FACING_RIGHT;
			animation.eraser();
			char imagePath[] = ".\\Bitmaps\\HERO\\0\\hero_x.bmp";
			for (int i = 0; i < 10; i++) {
				imagePath[22] = '0' + i;
				animation.AddBitmap(imagePath, RGB(0, 255, 0));
			}
			animation.AddBitmap(".\\Bitmaps\\HERO\\0\\hero_10.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\HERO\\0\\hero_11.bmp", RGB(0, 255, 0));
		}
		else if (face == HERO_FACING_LEFT && faceDirection == HERO_FACING_RIGHT) {
			faceDirection = HERO_FACING_LEFT;
			animation.eraser();
			char imagePath[] = ".\\Bitmaps\\HERO\\0\\hero_x_flip.bmp";
			for (int i = 0; i < 10; i++) {
				imagePath[22] = '0' + i;
				animation.AddBitmap(imagePath, RGB(0, 255, 0));
			}
			animation.AddBitmap(".\\Bitmaps\\HERO\\0\\hero_10_flip.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\HERO\\0\\hero_11_flip.bmp", RGB(0, 255, 0));
		}
	}

	void HHero::OnMove() {
		animation.OnMove();
		if (!isMoving)
			return;

		stepCounter += stepPerTick;
		switch (movingDirection) {
		case HERO_MOVE_UP:
			y -= stepPerTick;
			if (stepCounter >= maximumSteps) {
				onMapY -= 1;
			}
			break;
		case HERO_MOVE_DOWN:
			y += stepPerTick;
			if (stepCounter >= maximumSteps) {
				onMapY += 1;
			}
			break;
		case HERO_MOVE_LEFT:
			x -= stepPerTick;
			if (stepCounter >= maximumSteps) {
				onMapX -= 1;
			}
			
			break;
		case HERO_MOVE_RIGHT:
			x += stepPerTick;
			if (stepCounter >= maximumSteps) {
				onMapX += 1;
			}
			
			break;
		default:
			break;
		}
		

		if (stepCounter >= maximumSteps) {
			isMoving = false;
			movingDirection = HERO_NOT_MOVING;
			stepCounter = 0;
		}


	}

	void HHero::OnShow() {
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}

	int HHero::GetX1() { return x; }
	int HHero::GetY1() { return y; }
	int HHero::GetX2() { return x + animation.Width(); }
	int HHero::GetY2() { return y + animation.Height(); }

	int HHero::getXOnMap() { return onMapX; }
	int HHero::getYOnMap() { return onMapY; }
}