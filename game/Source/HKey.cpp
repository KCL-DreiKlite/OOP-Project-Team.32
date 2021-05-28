#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "HKey.h"

#include "HMapObject.h"


namespace game_framework {


	HKey::HKey() {

	}

	void HKey::Initialize(int onMapX, int onMapY, int objectWidth) {
		HMapObject::Initialize(onMapX, onMapY, objectWidth);
	}

	void HKey::LoadBitmap() {

		animation.AddBitmap(".\\Bitmaps\\KEY\\key_0.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\KEY\\key_1.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\KEY\\key_2.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\KEY\\key_3.bmp", RGB(0, 255, 0));
		
	}

	void HKey::OnMove() {
		animation.OnMove();
	}

	void HKey::OnShow() {
		if (is_alive) {
			animation.SetTopLeft(x, y);
			animation.OnShow();
		}
	}

	void HKey::SetIsAlive(bool alive) {
		is_alive = alive;
		if (!is_alive) {
			onMapX = 0;
			onMapY = 0;
		}
	}

	bool HKey::IsAlive() {
		return is_alive;
	}

}