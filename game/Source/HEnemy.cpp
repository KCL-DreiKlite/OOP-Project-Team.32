#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "HEnemy.h"

namespace game_framework {
	HEnemy::HEnemy() {

	}

	void HEnemy::Initialize(int x, int y, int xOnMap, int yOnMap) {
		this->x = x; this->y = y;
		this->onMapX = xOnMap; this->onMapY = yOnMap;

		isMoving = false;
		stepCounter = 0;
		movingDirection = ENEMY_NOT_MOVING;
	}

	void HEnemy::LoadBitmap() {
		animation.AddBitmap(".\\Bitmaps\\skeleton\\0\\skeleton_0.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\skeleton\\0\\skeleton_1.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\skeleton\\0\\skeleton_2.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\skeleton\\0\\skeleton_3.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\skeleton\\0\\skeleton_4.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\skeleton\\0\\skeleton_5.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\skeleton\\0\\skeleton_6.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\skeleton\\0\\skeleton_7.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\skeleton\\0\\skeleton_8.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\skeleton\\0\\skeleton_9.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\skeleton\\0\\skeleton_10.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\skeleton\\0\\skeleton_11.bmp", RGB(0, 255, 0));
	}

	void HEnemy::SetXY(int nx, int ny) {
		x = nx; y = ny;
	}

	void HEnemy::SetMovingDirection(char direction) {
		if (isMoving)
			return;

		isMoving = true;
		movingDirection = direction;
	}

	void HEnemy::OnMove() {
		animation.OnMove();
		if (!isMoving)
			return;

		stepCounter += stepPerTick;
		switch (movingDirection) {
		case ENEMY_MOVE_UP:
			y -= stepPerTick;
			if (stepCounter >= maximumSteps) {
				onMapY -= 1;
			}
			break;
		case ENEMY_MOVE_DOWN:
			y += stepPerTick;
			if (stepCounter >= maximumSteps) {
				onMapY += 1;
			}
			break;
		case ENEMY_MOVE_LEFT:
			x -= stepPerTick;
			if (stepCounter >= maximumSteps) {
				onMapX -= 1;
			}

			break;
		case ENEMY_MOVE_RIGHT:
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
			movingDirection = ENEMY_NOT_MOVING;
			stepCounter = 0;
		}


	}

	void HEnemy::OnShow() {
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}

	int HEnemy::getX1() { return x; }
	int HEnemy::getY1() { return y; }
	int HEnemy::getX2() { return x + animation.Width(); }
	int HEnemy::getY2() { return y + animation.Height(); }

	int HEnemy::getXOnMap() { return onMapX; }
	int HEnemy::getYOnMap() { return onMapY; }
}