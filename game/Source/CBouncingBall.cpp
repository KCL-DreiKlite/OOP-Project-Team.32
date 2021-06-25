#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBouncingBall.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBouncingBall: BouncingBall class
	/////////////////////////////////////////////////////////////////////////////

	CBouncingBall::CBouncingBall()
	{
		const int INITIAL_VELOCITY = 5;	// 嚙踝蕭l嚙磕嚙褕速嚙踝蕭
		const int FLOOR = 400;				// 嚙窮嚙瞌嚙緙嚙踝蕭
		floor = FLOOR;
		x = 95; y = FLOOR - 1;				// y嚙緙嚙請歹蕭a嚙瞌嚙踝蕭1嚙瘢(嚙踝蕭嚙箭嚙窮嚙瞌嚙磕)
		rising = true;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		
	}

	void CBouncingBall::LoadBitmap()
	{
		//char *filename[12] = { ".\\Bitmaps\\LUCIFER\\lucifer_0.png",".\\Bitmaps\\LUCIFER\\lucifer_1.png",".\\Bitmaps\\LUCIFER\\lucifer_2.png",".\\Bitmaps\\LUCIFER\\lucifer_3.png",".\\Bitmaps\\LUCIFER\\lucifer_4.png",".\\Bitmaps\\LUCIFER\\lucifer_5.png",".\\Bitmaps\\LUCIFER\\lucifer_6.png",".\\Bitmaps\\LUCIFER\\lucifer_7.png",".\\Bitmaps\\LUCIFER\\lucifer_8.png",".\\Bitmaps\\LUCIFER\\lucifer_9.png",".\\Bitmaps\\LUCIFER\\lucifer_10.png",".\\Bitmaps\\LUCIFER\\lucifer_11.png"};
		//for (int i = 0; i < 8; i++)	// 嚙踝蕭嚙皚嚙褊畫(嚙踝蕭4嚙箠嚙誕形構嚙踝蕭)
		//	animation.AddBitmap(filename[i], RGB(0, 0, 0));
		char imagePath[] = ".\\Bitmaps\\HERO\\0\\hero_x.bmp";
		for (int i = 0; i < 10; i++) {
			imagePath[22] = '0' + i;
			animation.AddBitmap(imagePath, RGB(0, 255, 0));
		}
	}

	void CBouncingBall::OnMove()
	{
		if (rising) {			// 嚙磕嚙褕迎蕭嚙璀
			if (velocity > 0) {
				y -= velocity;	// 嚙踝蕭嚙緣嚙踝蕭 > 0嚙褕，y嚙箭嚙磕嚙踝蕭(嚙踝蕭嚙踝蕭velocity嚙踝蕭嚙瘢嚙璀velocity嚙踝蕭嚙踝蕭鴐� 嚙瘢/嚙踝蕭)
				velocity--;		// 嚙踝蕭嚙踝蕭嚙瞌嚙緞嚙確嚙璀嚙磊嚙踝蕭嚙踝蕭嚙磕嚙褕速嚙論哨蕭嚙瘠
			}
			else {
				rising = false; // 嚙踝蕭嚙緣嚙踝蕭 <= 0嚙璀嚙磕嚙褕終歹蕭A嚙磊嚙踝蕭嚙踝為嚙磊嚙踝蕭
				velocity = 1;	// 嚙磊嚙踝蕭嚙踝蕭嚙踝蕭t(velocity)嚙踝蕭1
			}
		}
		else {				// 嚙磊嚙踝蕭嚙踝蕭嚙璀
			if (y < floor - 1) {  // 嚙踝蕭y嚙緙嚙踝蕭嚙誶沒嚙瘢嚙踝蕭a嚙瞌
				y += velocity;	// y嚙箭嚙磊嚙踝蕭(嚙踝蕭嚙踝蕭velocity嚙踝蕭嚙瘢嚙璀velocity嚙踝蕭嚙踝蕭鴐� 嚙瘢/嚙踝蕭)
				velocity++;		// 嚙踝蕭嚙踝蕭嚙瞌嚙緞嚙確嚙璀嚙磊嚙踝蕭嚙踝蕭嚙磊嚙踝蕭嚙緣嚙論增嚙稼
			}
			else {
				y = floor - 1;  // 嚙踝蕭y嚙緙嚙請低嚙踝蕭a嚙瞌嚙璀嚙踟正穿蕭嚙窮嚙瞌嚙磕
				rising = true;	// 嚙踝蕭嚙踝蕭嚙誕彈嚙璀嚙磊嚙踝蕭嚙踝為嚙磕嚙踝蕭
				velocity = initial_velocity; // 嚙踝蕭嚙稽嚙磕嚙褕迎蕭l嚙緣嚙踝蕭
			}
		}
		animation.OnMove();		// 嚙踝蕭嚙踝蕭@嚙踝蕭animation.OnMove()嚙璀animation嚙羯嚙罵嚙踝蕭嚙踝蕭
	}

	void CBouncingBall::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}