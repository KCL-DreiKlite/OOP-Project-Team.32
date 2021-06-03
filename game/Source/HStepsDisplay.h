
namespace game_framework {
#define DIGIT_0_BITMAP ".\\Bitmaps\\DIGITS\\digit_0.bmp"
#define DIGIT_1_BITMAP ".\\Bitmaps\\DIGITS\\digit_1.bmp"
#define DIGIT_2_BITMAP ".\\Bitmaps\\DIGITS\\digit_2.bmp"
#define DIGIT_3_BITMAP ".\\Bitmaps\\DIGITS\\digit_3.bmp"
#define DIGIT_4_BITMAP ".\\Bitmaps\\DIGITS\\digit_4.bmp"
#define DIGIT_5_BITMAP ".\\Bitmaps\\DIGITS\\digit_5.bmp"
#define DIGIT_6_BITMAP ".\\Bitmaps\\DIGITS\\digit_6.bmp"
#define DIGIT_7_BITMAP ".\\Bitmaps\\DIGITS\\digit_7.bmp"
#define DIGIT_8_BITMAP ".\\Bitmaps\\DIGITS\\digit_8.bmp"
#define DIGIT_9_BITMAP ".\\Bitmaps\\DIGITS\\digit_9.bmp"

#define DEFAULT_DISPLAY_WIDTH 44
#define DEFAULT_DISPLAY_HEIGHT 80
#define DEFAULT_DISPLAY_DIGITS 2

#ifndef _HSTEPSDISPLAY_H_
#define _HSTEPSDISPLAY_H_

	class HStepsDisplay {
	public:
		HStepsDisplay();
		HStepsDisplay(int maxSteps = 0);

		void Initialize(int x, int y);
		void LoadBitmap();
		void OnMove();
		void OnShow();
		
		// Reduce one step. If currentStep is equal or less than 0, return false.
		bool reduceStep();

		// Set current steps.
		void setCurrentSteps(int currentSteps);

		// Reset current steps to default maximum.
		void resetCurrentSteps();

		int getCurrentSteps();

		int getX1();
		int getX2();
		int getY1();
		int getY2();

	protected:
		char* getDigitBitmapPathname(int digit);

		/*
		   3 4
		   ^ ^
		   | |
		   | 4 -> digit_0
		   30  -> digit_1
		*/
		CAnimation digit_0 = CAnimation();
		CAnimation digit_1 = CAnimation();

		int x, y;
		int currentSteps;
		int maxSteps;

		// When the currentSteps changed, this will be true.
		// When true, OnShow() should erase both animations and reload bitmaps.
		bool digitChanged = false;

	};

#endif // !_HSTEPSDISPLAY_H_

}