#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "HPrincess.h"

#include "HMapObject.h"


namespace game_framework {


	HPrincess::HPrincess() {

	}

	void HPrincess::Initialize(int onMapX, int onMapY, int objectWidth) {
		HMapObject::Initialize(onMapX, onMapY, objectWidth);
	}

	void HPrincess::LoadBitmap(int whichPrincess) {
		this->whichPrincess = whichPrincess;

		if (whichPrincess == PRINCESS_LUCIFER) {
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_0.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_1.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_2.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_3.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_4.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_5.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_6.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_7.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_8.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_9.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_10.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\LUCIFER\\lucifer_11.bmp", RGB(0, 255, 0));
		}
	}


	void HPrincess::OnMove() {
		animation.OnMove();
	}

	void HPrincess::OnShow() {
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}


	int HPrincess::getWhichPrincess() { return whichPrincess; }
}