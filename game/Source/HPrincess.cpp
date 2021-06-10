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

	void HPrincess::Initialize(int onMapX, int onMapY, int xOffset, int yOffset, int objectWidth) {
		HMapObject::Initialize(onMapX, onMapY, xOffset, yOffset, objectWidth);
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
		else if (whichPrincess == PRINCESS_CERBERUS) {
			animation.AddBitmap(".\\Bitmaps\\CERBERUS\\0\\cerberus_0.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\CERBERUS\\0\\cerberus_1.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\CERBERUS\\0\\cerberus_2.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\CERBERUS\\0\\cerberus_3.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\CERBERUS\\0\\cerberus_4.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\CERBERUS\\0\\cerberus_5.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\CERBERUS\\0\\cerberus_6.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\CERBERUS\\0\\cerberus_7.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\CERBERUS\\0\\cerberus_8.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\CERBERUS\\0\\cerberus_9.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\CERBERUS\\0\\cerberus_10.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\CERBERUS\\0\\cerberus_11.bmp", RGB(0, 255, 0));
		}
		else if (whichPrincess == PRINCESS_AZAZEL) {
			animation.AddBitmap(".\\Bitmaps\\AZAZEL\\azazel_0.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\AZAZEL\\azazel_1.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\AZAZEL\\azazel_2.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\AZAZEL\\azazel_3.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\AZAZEL\\azazel_4.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\AZAZEL\\azazel_5.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\AZAZEL\\azazel_6.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\AZAZEL\\azazel_7.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\AZAZEL\\azazel_8.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\AZAZEL\\azazel_9.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\AZAZEL\\azazel_10.bmp", RGB(0, 255, 0));
			animation.AddBitmap(".\\Bitmaps\\AZAZEL\\azazel_11.bmp", RGB(0, 255, 0));
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