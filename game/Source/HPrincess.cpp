#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "HPrincess.h"


namespace game_framework {


	HPrincess::HPrincess() {

	}

	void HPrincess::Initialize() {
		x = 500; y = 300;
		onMapX = 5;
		onMapY = 3;

	}

	void HPrincess::LoadBitmap(int whichPrincess) {
		this->whichPrincess = whichPrincess;

		if (whichPrincess == PRINCESS_LUCIFER) {
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_0.bmp", RGB(255, 242, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_1.bmp", RGB(255, 242, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_2.bmp", RGB(255, 242, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_3.bmp", RGB(255, 242, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_4.bmp", RGB(255, 242, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_5.bmp", RGB(255, 242, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_6.bmp", RGB(255, 242, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_7.bmp", RGB(255, 242, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_8.bmp", RGB(255, 242, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_9.bmp", RGB(255, 242, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_10.bmp", RGB(255, 242, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_11.bmp", RGB(255, 242, 0));
		}
	}

	void HPrincess::SetXY(int nx, int ny) {
		x = nx; y = ny;
	}

	void HPrincess::OnMove() {

	}

	void HPrincess::OnShow() {
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}


	int HPrincess::GetX1() { return x; }
	int HPrincess::GetY1() { return y; }
	int HPrincess::GetX2() { return x + animation.Width(); }
	int HPrincess::GetY2() { return y + animation.Height(); }

	int HPrincess::getXOnMap() { return onMapX; }
	int HPrincess::getYOnMap() { return onMapY; }
}