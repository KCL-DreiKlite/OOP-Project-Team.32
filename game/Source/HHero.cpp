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

	void HHero::OnMove(bool movableMap[][11]) {
		animation.OnMove();
		if (!isMoving)
			return;

		stepCounter += stepPerTick;
		switch (movingDirection) {
		case HERO_MOVE_UP:
			if (movableMap[onMapY-1][onMapX]){
				y -= stepPerTick;
				if (stepCounter >= 100) {
					onMapY -= 1;
				}
			}
			break;
		case HERO_MOVE_DOWN:
			if (movableMap[onMapY + 1][onMapX]){
				y += stepPerTick;
				if (stepCounter >= 100) {
					onMapY += 1;
				}
			}
			break;
		case HERO_MOVE_LEFT:
			if (movableMap[onMapY][onMapX-1]) {
				x -= stepPerTick;
				if (stepCounter >= 100) {
					onMapX -= 1;
				}
			}
			
			break;
		case HERO_MOVE_RIGHT:
			if (movableMap[onMapY][onMapX + 1]) {
				x += stepPerTick;
				if (stepCounter >= 100) {
					onMapX += 1;
				}
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