#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "HRock.h"

namespace game_framework {
	HRock::HRock() {
		is_alive = true;
	}

	void HRock::Initialize(int xOnMap, int yOnMap, int objectWidth) {
		this->onMapX = xOnMap; this->onMapY = yOnMap;
		this->x = xOnMap * objectWidth; this->y = yOnMap * objectWidth;

		isMoving = false;
		stepCounter = 0;
		movingDirection = ROCK_NOT_MOVING;
	}

	void HRock::LoadBitmap(int whichRockImage) {
		this->whichRockImage = whichRockImage;
		
		//if (whichRock == ROCK_BMP_0)
		//	animation.AddBitmap(".\\rock_0.bmp", RGB(0, 255, 0));
		switch (whichRockImage) {
		case ROCK_BMP_0:
			animation.AddBitmap(".\\Bitmaps\\rock\\rock_0.bmp", RGB(0, 255, 0));
			break;
		case ROCK_BMP_1:
			animation.AddBitmap(".\\Bitmaps\\rock\\rock_1.bmp", RGB(0, 255, 0));
			break;
		case ROCK_BMP_2:
			animation.AddBitmap(".\\Bitmaps\\rock\\rock_2.bmp", RGB(0, 255, 0));
			break;
		default:
			break;
		}
		//animation.AddBitmap(".\\Bitmaps\\rock\\rock_0.bmp", RGB(0, 255, 0));
		//animation.AddBitmap(".\\Bitmaps\\rock\\rock_1.bmp", RGB(0, 255, 0));
		//animation.AddBitmap(".\\Bitmaps\\rock\\rock_2.bmp", RGB(0, 255, 0));
	}

	void HRock::SetXY(int nx, int ny) {
		x = nx; y = ny;
	}

	void HRock::SetMovingDirection(char direction) {
		if (isMoving)
			return;

		isMoving = true;
		movingDirection = direction;
	}

	void HRock::OnMove() {
		animation.OnMove();
		if (!isMoving)
			return;

		stepCounter += stepPerTick;
		switch (movingDirection) {
		case ROCK_MOVE_UP:
			y -= stepPerTick;
			if (stepCounter >= maximumSteps) {
				onMapY -= 1;
			}
			break;
		case ROCK_MOVE_DOWN:
			y += stepPerTick;
			if (stepCounter >= maximumSteps) {
				onMapY += 1;
			}
			break;
		case ROCK_MOVE_LEFT:
			x -= stepPerTick;
			if (stepCounter >= maximumSteps) {
				onMapX -= 1;
			}

			break;
		case ROCK_MOVE_RIGHT:
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
			movingDirection = ROCK_NOT_MOVING;
			stepCounter = 0;
		}
	}

	void HRock::SetIsAlive(bool alive) {
		is_alive = alive;
		if (!is_alive) {
			onMapX = 0;
			onMapY = 0;
		}
	}

	void HRock::OnShow() {
		if (is_alive) {
			animation.SetTopLeft(x, y);
			animation.OnShow();
		}
	}

	int HRock::getX1() { return x; }
	int HRock::getY1() { return y; }
	int HRock::getX2() { return x + animation.Width(); }
	int HRock::getY2() { return y + animation.Height(); }

	int HRock::getXOnMap() { return onMapX; }
	int HRock::getYOnMap() { return onMapY; }
}