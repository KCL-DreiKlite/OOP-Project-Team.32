#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "HLock.h"


namespace game_framework {


	HLock::HLock() {

	}

	void HLock::Initialize() {
		x = 500; y = 300;
		onMapX = 5;
		onMapY = 3;
	}

	void HLock::LoadBitmap() {

		animation.AddBitmap(".\\Bitmaps\\LOCK\\lock.bmp", RGB(0, 255, 0));
	}

	void HLock::SetXY(int nx, int ny) {
		x = nx; y = ny;
	}

	void HLock::OnMove() {
		animation.OnMove();
	}

	void HLock::OnShow() {
		if (is_alive) {
			animation.SetTopLeft(x, y);
			animation.OnShow();
		}
	}

	void HLock::SetIsAlive(bool alive) {
		is_alive = alive;
		if (!is_alive) {
			onMapX = 0;
			onMapY = 0;
		}
	}

	int HLock::GetX1() { return x; }
	int HLock::GetY1() { return y; }
	int HLock::GetX2() { return x + animation.Width(); }
	int HLock::GetY2() { return y + animation.Height(); }

	int HLock::getXOnMap() { return onMapX; }
	int HLock::getYOnMap() { return onMapY; }
}