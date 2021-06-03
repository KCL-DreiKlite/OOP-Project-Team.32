#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "HStepsDisplay.h"

namespace game_framework {
	HStepsDisplay::HStepsDisplay() {}
	HStepsDisplay::HStepsDisplay(int maxSteps) {
		this->maxSteps = this->currentSteps = maxSteps;
		
	}

	void HStepsDisplay::Initialize(int x, int y) {
		this->x = x; this->y = y;

	}

	void HStepsDisplay::LoadBitmap() {
		//char digit_bitmap_base[] = ".\\Bitmaps\\DIGITS\\digit_0.bmp";
		//const int changeIndex = 23;
		//for (int index = 0; index <= 9; index++) {
		//	digit_bitmap_base[changeIndex] = index + '0';
		//}

		digit_1.AddBitmap(getDigitBitmapPathname(currentSteps / 10), RGB(0, 0, 0));
		digit_0.AddBitmap(getDigitBitmapPathname(currentSteps % 10), RGB(0, 0, 0));

		digit_1.SetTopLeft(x, y);
		digit_0.SetTopLeft(x + DEFAULT_DISPLAY_WIDTH, y);

	}

	void HStepsDisplay::OnMove() {
		digit_1.OnMove();
		digit_0.OnMove();
	}

	void HStepsDisplay::OnShow() {
		if (digitChanged) {
			digit_1.eraser();
			digit_0.eraser();

			digit_1.AddBitmap(getDigitBitmapPathname(currentSteps / 10), RGB(0, 0, 0));
			digit_0.AddBitmap(getDigitBitmapPathname(currentSteps % 10), RGB(0, 0, 0));

		}

		digit_1.SetTopLeft(x, y);
		digit_0.SetTopLeft(x + DEFAULT_DISPLAY_WIDTH, y);

		digit_1.OnShow();
		digit_0.OnShow();

		digitChanged = false;
	}

	bool HStepsDisplay::reduceStep() {
		digitChanged = true;

		if (currentSteps-- <= 0) {
			currentSteps = 0;
			return false;
		}
		return true;
	}

	void HStepsDisplay::setCurrentSteps(int currentSteps) {
		digitChanged = true;

		this->currentSteps = currentSteps;
	}

	void HStepsDisplay::resetCurrentSteps() {
		digitChanged = true;

		currentSteps = maxSteps;
	}


	char* HStepsDisplay::getDigitBitmapPathname(int digit) {
		switch (digit) {
		case 1:
			return DIGIT_1_BITMAP;
		case 2:
			return DIGIT_2_BITMAP;
		case 3:
			return DIGIT_3_BITMAP;
		case 4:
			return DIGIT_4_BITMAP;
		case 5:
			return DIGIT_5_BITMAP;
		case 6:
			return DIGIT_6_BITMAP;
		case 7:
			return DIGIT_7_BITMAP;
		case 8:
			return DIGIT_8_BITMAP;
		case 9:
			return DIGIT_9_BITMAP;
		default:
			return DIGIT_0_BITMAP;
		}
	}

	int HStepsDisplay::getCurrentSteps() { return currentSteps; }
	int HStepsDisplay::getX1() { return x; }
	int HStepsDisplay::getY1() { return y; }
	int HStepsDisplay::getX2() { return x + DEFAULT_DISPLAY_WIDTH * DEFAULT_DISPLAY_DIGITS; }
	int HStepsDisplay::getY2() { return y + DEFAULT_DISPLAY_HEIGHT; }

}