#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "HLock.h"

#include "HMapObject.h"

namespace game_framework {


	HLock::HLock() {

	}

	void HLock::Initialize(int onMapX, int onMapY, int objectWidth) {
		HMapObject::Initialize(onMapX, onMapY, objectWidth);
	}

	void HLock::LoadBitmap() {

		animation.AddBitmap(".\\Bitmaps\\LOCK\\lock.bmp", RGB(0, 255, 0));
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

}