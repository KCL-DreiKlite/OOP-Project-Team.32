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
		const int INITIAL_VELOCITY = 5;	// ��l�W�ɳt��
		const int FLOOR = 400;				// �a�O�y��
		floor = FLOOR;
		x = 95; y = FLOOR - 1;				// y�y�Ф�a�O��1�I(���b�a�O�W)
		rising = true;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		
	}

	void CBouncingBall::LoadBitmap()
	{
		//char *filename[12] = { ".\\Bitmaps\\LUCIFER\\lucifer_0.png",".\\Bitmaps\\LUCIFER\\lucifer_1.png",".\\Bitmaps\\LUCIFER\\lucifer_2.png",".\\Bitmaps\\LUCIFER\\lucifer_3.png",".\\Bitmaps\\LUCIFER\\lucifer_4.png",".\\Bitmaps\\LUCIFER\\lucifer_5.png",".\\Bitmaps\\LUCIFER\\lucifer_6.png",".\\Bitmaps\\LUCIFER\\lucifer_7.png",".\\Bitmaps\\LUCIFER\\lucifer_8.png",".\\Bitmaps\\LUCIFER\\lucifer_9.png",".\\Bitmaps\\LUCIFER\\lucifer_10.png",".\\Bitmaps\\LUCIFER\\lucifer_11.png"};
		//for (int i = 0; i < 8; i++)	// ���J�ʵe(��4�i�ϧκc��)
		//	animation.AddBitmap(filename[i], RGB(0, 0, 0));
		char imagePath[] = ".\\Bitmaps\\HERO\\0\\hero_x.bmp";
		for (int i = 0; i < 10; i++) {
			imagePath[22] = '0' + i;
			animation.AddBitmap(imagePath, RGB(0, 255, 0));
		}
	}

	void CBouncingBall::OnMove()
	{
		if (rising) {			// �W�ɪ��A
			if (velocity > 0) {
				y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
				velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
			}
			else {
				rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
				velocity = 1;	// �U������t(velocity)��1
			}
		}
		else {				// �U�����A
			if (y < floor - 1) {  // ��y�y���٨S�I��a�O
				y += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
				velocity++;		// �����O�v�T�A�U�����U���t�׼W�[
			}
			else {
				y = floor - 1;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W
				rising = true;	// �����ϼu�A�U���אּ�W��
				velocity = initial_velocity; // ���]�W�ɪ�l�t��
			}
		}
		animation.OnMove();		// ����@��animation.OnMove()�Aanimation�~�|����
	}

	void CBouncingBall::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}