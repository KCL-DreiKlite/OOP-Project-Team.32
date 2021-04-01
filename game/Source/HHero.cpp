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
		const int X_POS = 200;
		const int Y_POS = 100;
		x = X_POS;
		y = Y_POS;
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

	void HHero::SetMovingDirection(char direction) {
		if (isMoving)
			return;

		isMoving = true;
		movingDirection = direction;
	}

	void HHero::SetXY(int nx, int ny) {
		x = nx; y = ny;
	}

	void HHero::OnMove(bool movableMap[][], int x, int y) {
		animation.OnMove();
		if (!isMoving)
			return;

		switch (movingDirection) {
		case HERO_MOVE_UP:
			y -= stepPerTick;
			break;
		case HERO_MOVE_DOWN:
			y += stepPerTick;
			break;
		case HERO_MOVE_LEFT:
			x -= stepPerTick;
			break;
		case HERO_MOVE_RIGHT:
			x += stepPerTick;
			break;
		default:
			break;
		}
		stepCounter += stepPerTick;

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

}