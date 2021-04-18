#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "HKey.h"


namespace game_framework {


	HKey::HKey() {

	}

	void HKey::Initialize() {
		x = 900; y = 500;
		onMapX = 9;
		onMapY = 5;
	}

	void HKey::LoadBitmap() {

		animation.AddBitmap(".\\Bitmaps\\KEY\\key_0.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\KEY\\key_1.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\KEY\\key_2.bmp", RGB(0, 255, 0));
		animation.AddBitmap(".\\Bitmaps\\KEY\\key_3.bmp", RGB(0, 255, 0));
		
	}

	void HKey::SetXY(int nx, int ny) {
		x = nx; y = ny;
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

	int HKey::GetX1() { return x; }
	int HKey::GetY1() { return y; }
	int HKey::GetX2() { return x + animation.Width(); }
	int HKey::GetY2() { return y + animation.Height(); }

	int HKey::getXOnMap() { return onMapX; }
	int HKey::getYOnMap() { return onMapY; }
}