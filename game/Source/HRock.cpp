#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "HRock.h"

namespace game_framework {
	HRock::HRock() {

	}

	void HRock::Initialize(int x, int y, int xOnMap, int yOnMap) {
		this->x = x; this->y = y;
		this->onMapX = xOnMap; this->onMapY = yOnMap;

		isMoving = false;
		stepCounter = 0;
		movingDirection = ROCK_NOT_MOVING;
	}

	void HRock::LoadBitmap(int whichRock) {
		this->whichRock = whichRock;
		
		//if (whichRock == ROCK_BMP_0)
		//	animation.AddBitmap(".\\rock_0.bmp", RGB(0, 255, 0));
		switch (whichRock) {
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

	void HRock::OnShow() {
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}

	int HRock::getX1() { return x; }
	int HRock::getY1() { return y; }
	int HRock::getX2() { return x + animation.Width(); }
	int HRock::getY2() { return y + animation.Height(); }

	int HRock::getXOnMap() { return onMapX; }
	int HRock::getYOnMap() { return onMapY; }
}