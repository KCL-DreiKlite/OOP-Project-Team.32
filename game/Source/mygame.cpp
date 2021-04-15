/*
 * mygame.cpp: 嚙踝蕭嚙褕殷蕭嚙綞嚙瘠嚙踝蕭嚙踝蕭嚙踝蕭嚙踝蕭class嚙踝蕭implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 嚙緻嚙踝蕭class嚙踝蕭嚙瘠嚙踝蕭嚙踝蕭嚙瘠嚙踝蕭嚙罷嚙磐嚙箴嚙踝蕭嚙踝蕭嚙踝蕭
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 嚙踝蕭嚙誕很多嚙褕，OnInit嚙踝蕭嚙皚嚙課佗蕭嚙踝蕭嚙誕要嚙踝蕭雃h嚙褕塚蕭嚙瘠嚙踝蕭嚙論免嚙踝蕭嚙瘠嚙踝蕭嚙踝蕭嚙瘡
	//     嚙踝蕭嚙踝蕭嚙踝蕭嚙瑾嚙請，嚙瘠嚙踝蕭嚙罵嚙碼嚙緹嚙線Loading ...嚙緞嚙璀嚙踝蕭嚙盤oading嚙踝蕭嚙箠嚙論。
	//
	ShowInitProgress(0);	// 嚙瑾嚙罷嚙締嚙踝蕭loading嚙箠嚙論穿蕭0%
	//
	// 嚙罷嚙締嚙踝蕭嚙皚嚙踝蕭嚙�
	//
	logo.LoadBitmap(IDB_BACKGROUND);
	Sleep(300);				// 嚙踝蕭C嚙璀嚙瘡嚙皺嚙豎清嚙踝蕭嚙箠嚙論，嚙踝蕭盚C嚙踝蕭嚙請刪嚙踝蕭嚙踝蕭Sleep
	//
	// 嚙踝蕭OnInit嚙褊作嚙罵嚙踝蕭嚙踝蕭CGameStaterRun::OnInit()嚙璀嚙課以嚙箠嚙踝蕭嚙誶沒嚙踝蕭100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// 嚙踝蕭嚙踝蕭嚙踝蕭GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo 嚙踝蕭嚙踝蕭嚙瘠嚙踝蕭嚙踝蕭嚙踝蕭k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 嚙踝蕭嚙踝蕭嚙瘠嚙踝蕭
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// 嚙踝蕭嚙踝蕭嚙踝蕭GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// 嚙皺嚙磕logo
	//
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	//
	// Demo嚙衛對蕭嚙緝嚙踝蕭嚙踝蕭嚙誕用，嚙踝蕭嚙盤嚙罷嚙緻嚙褕請盡量嚙論免嚙踝蕭嚙踝蕭嚙誕用字嚙踝蕭嚙璀嚙踝蕭嚙瘠MovingBitmap嚙踝蕭嚙踝蕭n
	//
	CDC *pDC = CDDraw::GetBackCDC();			// 嚙踝蕭嚙緻 Back Plain 嚙踝蕭 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 嚙踝蕭嚙踝蕭 font f; 160嚙踝蕭嚙踝蕭16 point嚙踝蕭嚙緝
	fp=pDC->SelectObject(&f);					// 嚙踝蕭嚙� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// 嚙踝蕭 font f (嚙範嚙磊嚙踝蕭嚙緯嚙罵嚙瘤嚙踝蕭)
	CDDraw::ReleaseBackCDC();					// 嚙踝蕭 Back Plain 嚙踝蕭 CDC
}								

/////////////////////////////////////////////////////////////////////////////
// 嚙緻嚙踝蕭class嚙踝蕭嚙瘠嚙踝蕭嚙踝蕭嚙踝蕭嚙踝蕭嚙踝蕭嚙璀(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	//
	// 嚙踝蕭嚙誕很多嚙褕，OnInit嚙踝蕭嚙皚嚙課佗蕭嚙踝蕭嚙誕要嚙踝蕭雃h嚙褕塚蕭嚙瘠嚙踝蕭嚙論免嚙踝蕭嚙瘠嚙踝蕭嚙踝蕭嚙瘡
	//     嚙踝蕭嚙踝蕭嚙踝蕭嚙瑾嚙請，嚙瘠嚙踝蕭嚙罵嚙碼嚙緹嚙線Loading ...嚙緞嚙璀嚙踝蕭嚙盤oading嚙踝蕭嚙箠嚙論。
	//
	ShowInitProgress(66);	// 嚙踝蕭嚙諉前嚙瑾嚙諉迎蕭嚙璀嚙踝蕭嚙箠嚙論，嚙踝蕭嚙畿嚙箠嚙論蛛蕭嚙踝蕭66%
	//
	// 嚙罷嚙締嚙踝蕭嚙皚嚙踝蕭嚙�
	//
	Sleep(300);				// 嚙踝蕭C嚙璀嚙瘡嚙皺嚙豎清嚙踝蕭嚙箠嚙論，嚙踝蕭盚C嚙踝蕭嚙請刪嚙踝蕭嚙踝蕭Sleep
	//
	// 嚙諒終進嚙論穿蕭100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 嚙踝蕭嚙緻 Back Plain 嚙踝蕭 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 嚙踝蕭嚙踝蕭 font f; 160嚙踝蕭嚙踝蕭16 point嚙踝蕭嚙緝
	fp=pDC->SelectObject(&f);					// 嚙踝蕭嚙� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 嚙複字嚙踝蕭r嚙赭的嚙賞換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 嚙踝蕭 font f (嚙範嚙磊嚙踝蕭嚙緯嚙罵嚙瘤嚙踝蕭)
	CDDraw::ReleaseBackCDC();					// 嚙踝蕭 Back Plain 嚙踝蕭 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 嚙緻嚙踝蕭class嚙踝蕭嚙瘠嚙踝蕭嚙踝蕭嚙瘠嚙踝蕭嚙踝蕭嚙賣物嚙踝蕭A嚙瘩嚙緯嚙踝蕭嚙瘠嚙踝蕭嚙緹嚙踝蕭嚙踝蕭嚙箭嚙緻嚙踝蕭
/////////////////////////////////////////////////////////////////////////////


CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLS(28), stg1_rock_count(2), stg1_enemy_count(1)
{
	ball = new CBall [NUMBALLS];

	rocks = new HRock[stg1_rock_count];
	enemy = new HEnemy[stg1_enemy_count];
}

CGameStateRun::~CGameStateRun()
{
	delete [] ball;
	delete[] rocks;
}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 15;
	//for (int i = 0; i < NUMBALLS; i++) {				// 嚙稽嚙緩嚙緙嚙踝蕭嚙稻嚙締嚙緙嚙踝蕭
	//	int x_pos = i % BALL_PER_ROW;
	//	int y_pos = i / BALL_PER_ROW;
	//	ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
	//	ball[i].SetDelay(x_pos);
	//	ball[i].SetIsAlive(true);
	//}
	//eraser.Initialize();
	//background.SetTopLeft(BACKGROUND_X,0);				// 嚙稽嚙緩嚙瘢嚙踝蕭嚙踝蕭嚙稻嚙締嚙緙嚙踝蕭
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 嚙稽嚙緩嚙踝蕭嚙踝蕭嚙誕迎蕭嚙稻嚙締嚙緙嚙踝蕭
	hits_left.SetInteger(HITS_LEFT);					// 嚙踝蕭嚙緩嚙諸下嚙踝蕭嚙踝蕭嚙踝蕭嚙踝蕭
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 嚙踝蕭嚙緩嚙諸下嚙踝蕭嚙踝蕭嚙複迎蕭嚙緙嚙踝蕭
	//CAudio::Instance()->Play(AUDIO_LAKE, true);			// 嚙踝蕭嚙踝蕭 WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// 嚙踝蕭嚙踝蕭 WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// 嚙踝蕭嚙踝蕭 MIDI

	hero.Initialize();
	princess.Initialize();
	rocks[0].Initialize(600, 400, 6, 4);
	rocks[1].Initialize(300, 600, 3, 6);
	enemy[0].Initialize(500, 500, 5, 5);

	enemy[0].SetIsAlive(true);
}

void CGameStateRun::OnMove()							// 嚙踝蕭嚙褊遊嚙踝蕭嚙踝蕭嚙踝蕭
{
	//
	// 嚙緘嚙瘦嚙複梧蕭蚹嚙箱ursor嚙踝蕭嚙誼佗蕭嚙璀嚙篁嚙瞇嚙磊嚙踝蕭嚙緹嚙踝蕭嚙踝蕭commment嚙踝蕭嚙踝蕭嚙磐嚙箠
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// 嚙踝蕭嚙褊背嚙踝蕭嚙誕迎蕭嚙緙嚙踝蕭
	//
	//if (background.Top() > SIZE_Y)
	//	background.SetTopLeft(60 ,-background.Height());
	//background.SetTopLeft(background.Left(),background.Top()+1);
	//
	// 嚙踝蕭嚙褊球
	//
	//int i;
	//for (i=0; i < NUMBALLS; i++)
	//	ball[i].OnMove();
	//
	// 嚙踝蕭嚙踝蕭嚙踝蕭嚙締
	//
	//eraser.OnMove();
	//
	// 嚙瞑嚙稻嚙踝蕭嚙締嚙瞌嚙稻嚙瘢嚙踝蕭y
	//
	//for (i=0; i < NUMBALLS; i++)
	//	if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
	//		ball[i].SetIsAlive(false);
	//		CAudio::Instance()->Play(AUDIO_DING);
	//		hits_left.Add(-1);
	//		//
	//		// 嚙磐嚙諸餘嚙瘢嚙踝蕭嚙踝蕭嚙複穿蕭0嚙璀嚙篁嚙踝蕭嚙踝蕭Game Over嚙踝蕭嚙璀
	//		//
	//		if (hits_left.GetInteger() <= 0) {
	//			CAudio::Instance()->Stop(AUDIO_LAKE);	// 嚙踝蕭嚙踝蕭 WAVE
	//			CAudio::Instance()->Stop(AUDIO_NTUT);	// 嚙踝蕭嚙踝蕭 MIDI
	//			GotoGameState(GAME_STATE_OVER);
	//		}
	//	}
	//
	// 嚙踝蕭嚙褊彈嚙踝蕭嚙踝蕭嚙緙
	//
	//bball.OnMove();
	hero.OnMove();
	princess.OnMove();
	for (int i = 0; i < stg1_rock_count; i++)
		rocks[i].OnMove();
	for (int i = 0; i < stg1_enemy_count; i++)
		enemy[i].OnMove();

	//GET_MOVABLE(2, 3);
}

void CGameStateRun::OnInit()  								// 嚙瘠嚙踝蕭嚙踝蕭嚙踝蕭�及圖形設嚙緩
{
	//
	// 嚙踝蕭嚙誕很多嚙褕，OnInit嚙踝蕭嚙皚嚙課佗蕭嚙踝蕭嚙誕要嚙踝蕭雃h嚙褕塚蕭嚙瘠嚙踝蕭嚙論免嚙踝蕭嚙瘠嚙踝蕭嚙踝蕭嚙瘡
	//     嚙踝蕭嚙踝蕭嚙踝蕭嚙瑾嚙請，嚙瘠嚙踝蕭嚙罵嚙碼嚙緹嚙線Loading ...嚙緞嚙璀嚙踝蕭嚙盤oading嚙踝蕭嚙箠嚙論。
	//
	ShowInitProgress(33);	// 嚙踝蕭嚙諉前嚙瑾嚙諉迎蕭嚙璀嚙踝蕭嚙箠嚙論，嚙踝蕭嚙畿嚙箠嚙論蛛蕭嚙踝蕭33%
	//
	// 嚙罷嚙締嚙踝蕭嚙皚嚙踝蕭嚙�
	//
	//int i;
	//for (i = 0; i < NUMBALLS; i++)	
	//	ball[i].LoadBitmap();								// 嚙踝蕭嚙皚嚙踝蕭i嚙諉球嚙踝蕭嚙誕改蕭
	//eraser.LoadBitmap();
	//background.LoadBitmap(IDB_BACKGROUND);					// 嚙踝蕭嚙皚嚙瘢嚙踝蕭嚙踝蕭嚙誕改蕭
	//
	// 嚙踝蕭嚙踝蕭嚙踝蕭嚙踝蕭Loading嚙褊作嚙璀嚙踝蕭嚙踝蕭嚙箠嚙踝蕭
	//
	ShowInitProgress(50);
	Sleep(300); // 嚙踝蕭C嚙璀嚙瘡嚙皺嚙豎清嚙踝蕭嚙箠嚙論，嚙踝蕭盚C嚙踝蕭嚙請刪嚙踝蕭嚙踝蕭Sleep
	//
	// 嚙羯嚙踝蕭嚙踝蕭J嚙踝蕭L嚙踝蕭嚙�
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 嚙踝蕭嚙皚嚙踝蕭嚙踝蕭嚙踝蕭嚙誕改蕭
	corner.LoadBitmap(IDB_CORNER);							// 嚙踝蕭嚙皚嚙踝蕭嚙踝蕭嚙誕改蕭
	//corner.ShowBitmap(background);							// 嚙瞇corner嚙皺嚙踝蕭background
	//bball.LoadBitmap();										// 嚙踝蕭嚙皚嚙誕改蕭
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 嚙踝蕭嚙皚嚙編嚙踝蕭0嚙踝蕭嚙緯嚙踝蕭ding.wav
	//CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 嚙踝蕭嚙皚嚙編嚙踝蕭1嚙踝蕭嚙緯嚙踝蕭lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\bgm1.mp3");	// 嚙踝蕭嚙皚嚙編嚙踝蕭2嚙踝蕭嚙緯嚙踝蕭ntut.mid
	//
	// 嚙踝蕭OnInit嚙褊作嚙罵嚙踝蕭嚙踝蕭CGameStaterOver::OnInit()嚙璀嚙課以嚙箠嚙踝蕭嚙誶沒嚙踝蕭100%
	//
	gamemap.LoadBitMap(); //嚙窮嚙踝蕭


	hero.LoadBitmap();
	princess.LoadBitmap(PRINCESS_LUCIFER);
	//rock_0.LoadBitmap(ROCK_BMP_0);
	for (int i = 0; i < stg1_rock_count; i++) {
		switch (i % 3) {
		case 0:
			rocks[i].LoadBitmap(ROCK_BMP_0);
			break;
		case 1:
			rocks[i].LoadBitmap(ROCK_BMP_1);
			break;
		case 2:
			rocks[i].LoadBitmap(ROCK_BMP_2);
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < stg1_enemy_count; i++)
		enemy[i].LoadBitmap();


}

void CGameStateRun::HeroWantToMove(char direction) {
	// Check if hero touched princess
	const int px = princess.getXOnMap(), py = princess.getYOnMap();
	const int hx = hero.getXOnMap(), hy = hero.getYOnMap();

	// 4 steps to move hero:
	// 1. Check if hero want to crash the edge
	// 2. Check if hero touched the rock. If so, then move rock
	// 3. Check if hero touched princess. If so, then game over
	// 4. Check if hero touched the enemy. If so, then move enemy
	// 5. If non of these conditions is true, then move hero.

	if (direction == HERO_MOVE_UP) {
		// Check if hero want to crash the edge
		if (!stg1_mapEdge[hy - 1][hx])
			return;

		// Check if hero touched the rock
		int touchedRock = -1;
		int rockTouchedObject = -1;
		for (int i = 0; i < stg1_rock_count; i++) {
			const int rx = rocks[i].getXOnMap(), ry = rocks[i].getYOnMap();
			if (hx == rx && hy - 1 == ry) {
				touchedRock = i;
				// Check if the rock touched the enemy
				for (int i = 0; i < stg1_enemy_count; i++) {
					const int ex = enemy[i].getXOnMap(), ey = enemy[i].getYOnMap();
					if (rx == ex && ry - 1 == ey) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
				}
				// Check if the rock touched the rock
				for (int j = 0; j < stg1_rock_count; j++) {
					const int rx0 = rocks[j].getXOnMap(), ry0 = rocks[j].getYOnMap();
					if (rx == rx0 && ry - 1 == ry0) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
				}
				// Check if the rock touched the princess
				if (rx == px && ry - 1 == py) {
					touchedRock = -1;
					rockTouchedObject = 1;
					break;
				}
				break;
			}
		}
		if (touchedRock != -1) {
			if (stg1_mapEdge[rocks[touchedRock].getYOnMap() - 1][rocks[touchedRock].getXOnMap()]) 
				rocks[touchedRock].SetMovingDirection(ROCK_MOVE_UP);	//rock moved
		}

		// Check if hero touched princess
		else if (hx == px && hy - 1 == py) {
			CAudio::Instance()->Stop(AUDIO_NTUT);
			GotoGameState(GAME_STATE_OVER);
		}

		// Check if hero touched enemy
		int touchedEnemy = -1;
		int enemyTouchedRock = -1;
		for (int i = 0; i < stg1_enemy_count; i++) {
			const int ex = enemy[i].getXOnMap(), ey = enemy[i].getYOnMap();
			if (hx == ex && hy - 1 == ey) {
				touchedEnemy = i;
				// Check if the enemy touched the rock
				for (int i = 0; i < stg1_rock_count; i++) {
					const int rx = rocks[i].getXOnMap(), ry = rocks[i].getYOnMap();
					if (ex == rx && ey - 1 == ry) {
						enemy[touchedEnemy].SetIsAlive(false);    //enemy died
						touchedEnemy = -1;
						enemyTouchedRock = 1;
						break;
					}
				}
				break;
			}
		}
		if (touchedEnemy != -1) {
			if (stg1_mapEdge[enemy[touchedEnemy].getYOnMap() - 1][enemy[touchedEnemy].getXOnMap()])
				enemy[touchedEnemy].SetMovingDirection(ENEMY_MOVE_UP);	//enemy moved
			else {
				enemy[touchedEnemy].SetIsAlive(false);    //enemy died
			}
		}

		// Everything's clear. Move hero
		if(touchedRock == -1 && touchedEnemy == -1 && rockTouchedObject == -1 && enemyTouchedRock == -1 )
			hero.SetMovingDirection(HERO_MOVE_UP);	//hero moved

	}
	else if (direction == HERO_MOVE_DOWN) {
		// Check if hero want to crash the edge
		if (!stg1_mapEdge[hy + 1][hx])
			return;

		// Check if hero touched the rock
		int touchedRock = -1;
		int rockTouchedObject = -1;
		for (int i = 0; i < stg1_rock_count; i++) {
			const int rx = rocks[i].getXOnMap(), ry = rocks[i].getYOnMap();
			if (hx == rx && hy + 1 == ry) {
				touchedRock = i;
				// Check if the rock touched the enemy
				for (int i = 0; i < stg1_enemy_count; i++) {
					const int ex = enemy[i].getXOnMap(), ey = enemy[i].getYOnMap();
					if (rx == ex && ry + 1 == ey) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
				}
				// Check if the rock touched the rock
				for (int j = 0; j < stg1_rock_count; j++) {
					const int rx0 = rocks[j].getXOnMap(), ry0 = rocks[j].getYOnMap();
					if (rx == rx0 && ry + 1 == ry0) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
				}
				// Check if the rock touched the princess
				if (rx == px && ry + 1 == py) {
					touchedRock = -1;
					rockTouchedObject = 1;
					break;
				}
				break;
			}
		}
		if (touchedRock != -1) {
			if (stg1_mapEdge[rocks[touchedRock].getYOnMap() + 1][rocks[touchedRock].getXOnMap()])
				rocks[touchedRock].SetMovingDirection(ROCK_MOVE_DOWN);	//rock moved
		}

		// Check if hero touched princess
		else if (hx == px && hy + 1 == py) {
			CAudio::Instance()->Stop(AUDIO_NTUT);
			GotoGameState(GAME_STATE_OVER);
		}

		// Check if hero touched enemy
		int touchedEnemy = -1;
		int enemyTouchedRock = -1;
		for (int i = 0; i < stg1_enemy_count; i++) {
			const int ex = enemy[i].getXOnMap(), ey = enemy[i].getYOnMap();
			if (hx == ex && hy + 1 == ey) {
				touchedEnemy = i;
				// Check if the enemy touched the rock
				for (int i = 0; i < stg1_rock_count; i++) {
					const int rx = rocks[i].getXOnMap(), ry = rocks[i].getYOnMap();
					if (ex == rx && ey + 1 == ry) {
						enemy[touchedEnemy].SetIsAlive(false);    //enemy died
						touchedEnemy = -1;
						enemyTouchedRock = 1;
						break;
					}
				}
				break;
			}
		}
		if (touchedEnemy != -1) {
			if (stg1_mapEdge[enemy[touchedEnemy].getYOnMap() + 1][enemy[touchedEnemy].getXOnMap()])
				enemy[touchedEnemy].SetMovingDirection(ENEMY_MOVE_DOWN);	//enemy moved
			else
				enemy[touchedEnemy].SetIsAlive(false);    //enemy died
		}

		// Everything's clear. Move hero
		if (touchedRock == -1 && touchedEnemy == -1 && rockTouchedObject == -1 && enemyTouchedRock == -1 )
			hero.SetMovingDirection(HERO_MOVE_DOWN);	//hero moved

	}
	else if (direction == HERO_MOVE_LEFT) {
		// Check if hero want to crash the edge
		if (!stg1_mapEdge[hy][hx - 1])
			return;

		// Check if hero touched the rock
		int touchedRock = -1;
		int rockTouchedObject = -1;
		for (int i = 0; i < stg1_rock_count; i++) {
			const int rx = rocks[i].getXOnMap(), ry = rocks[i].getYOnMap();
			if (hx - 1 == rx && hy == ry) {
				touchedRock = i;
				// Check if the rock touched the enemy
				for (int i = 0; i < stg1_enemy_count; i++) {
					const int ex = enemy[i].getXOnMap(), ey = enemy[i].getYOnMap();
					if (rx - 1 == ex && ry== ey) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
				}
				// Check if the rock touched the rock
				for (int j = 0; j < stg1_rock_count; j++) {
					const int rx0 = rocks[j].getXOnMap(), ry0 = rocks[j].getYOnMap();
					if (rx - 1 == rx0 && ry == ry0) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
				}
				// Check if the rock touched the princess
				if (rx - 1 == px && ry == py) {
					touchedRock = -1;
					rockTouchedObject = 1;
					break;
				}
				break;
			}
		}
		if (touchedRock != -1) {
			if (stg1_mapEdge[rocks[touchedRock].getYOnMap()][rocks[touchedRock].getXOnMap() - 1])
				rocks[touchedRock].SetMovingDirection(ROCK_MOVE_LEFT);	//rock moved
		}

		// Check if hero touched princess
		else if (hx - 1 == px && hy == py) {
			CAudio::Instance()->Stop(AUDIO_NTUT);
			GotoGameState(GAME_STATE_OVER);
		}

		// Check if hero touched enemy
		int touchedEnemy = -1;
		int enemyTouchedRock = -1;
		for (int i = 0; i < stg1_enemy_count; i++) {
			const int ex = enemy[i].getXOnMap(), ey = enemy[i].getYOnMap();
			if (hx - 1 == ex && hy == ey) {
				touchedEnemy = i;
				// Check if the enemy touched the rock
				for (int i = 0; i < stg1_rock_count; i++) {
					const int rx = rocks[i].getXOnMap(), ry = rocks[i].getYOnMap();
					if (ex - 1 == rx && ey == ry) {
						enemy[touchedEnemy].SetIsAlive(false);    //enemy died
						touchedEnemy = -1;
						enemyTouchedRock = 1;
						break;
					}
				}
				break;
			}
		}
		if (touchedEnemy != -1) {
			if (stg1_mapEdge[enemy[touchedEnemy].getYOnMap()][enemy[touchedEnemy].getXOnMap() - 1])
				enemy[touchedEnemy].SetMovingDirection(ENEMY_MOVE_LEFT);	//enemy moved
			else
				enemy[touchedEnemy].SetIsAlive(false);    //enemy died
		}

		// Everything's clear. Move hero
		if (touchedRock == -1 && touchedEnemy == -1 && rockTouchedObject == -1 && enemyTouchedRock == -1 )
			hero.SetMovingDirection(HERO_MOVE_LEFT);	//hero moved

	}
	else if (direction == HERO_MOVE_RIGHT) {
		// Check if hero want to crash the edge
		if (!stg1_mapEdge[hy][hx + 1])
			return;

		// Check if hero touched the rock
		int touchedRock = -1;
		int rockTouchedObject = -1;
		for (int i = 0; i < stg1_rock_count; i++) {
			const int rx = rocks[i].getXOnMap(), ry = rocks[i].getYOnMap();
			if (hx + 1 == rx && hy == ry) {
				touchedRock = i;
				// Check if the rock touched the enemy
				for (int i = 0; i < stg1_enemy_count; i++) {
					const int ex = enemy[i].getXOnMap(), ey = enemy[i].getYOnMap();
					if (rx + 1 == ex && ry == ey) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
				}
				// Check if the rock touched the rock
				for (int j = 0; j < stg1_rock_count; j++) {
					const int rx0 = rocks[j].getXOnMap(), ry0 = rocks[j].getYOnMap();
					if (rx + 1 == rx0 && ry == ry0) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
				}
				// Check if the rock touched the princess
				if (rx + 1 == px && ry == py) {
					touchedRock = -1;
					rockTouchedObject = 1;
					break;
				}
				break;
			}
		}
		if (touchedRock != -1) {
			if (stg1_mapEdge[rocks[touchedRock].getYOnMap()][rocks[touchedRock].getXOnMap() + 1])
				rocks[touchedRock].SetMovingDirection(ROCK_MOVE_RIGHT);	//rock moved
		}

		// Check if hero touched princess
		else if (hx + 1 == px && hy == py) {
			CAudio::Instance()->Stop(AUDIO_NTUT);
			GotoGameState(GAME_STATE_OVER);
		}

		// Check if hero touched enemy
		int touchedEnemy = -1;
		int enemyTouchedRock = -1;
		for (int i = 0; i < stg1_enemy_count; i++) {
			const int ex = enemy[i].getXOnMap(), ey = enemy[i].getYOnMap();
			if (hx + 1 == ex && hy == ey) {
				touchedEnemy = i;
				// Check if the enemy touched the rock
				for (int i = 0; i < stg1_rock_count; i++) {
					const int rx = rocks[i].getXOnMap(), ry = rocks[i].getYOnMap();
					if (ex + 1 == rx && ey == ry) {
						enemy[touchedEnemy].SetIsAlive(false);    //enemy died
						touchedEnemy = -1;
						enemyTouchedRock = 1;
						break;
					}
				}
				break;
			}
		}
		if (touchedEnemy != -1) {
			if (stg1_mapEdge[enemy[touchedEnemy].getYOnMap()][enemy[touchedEnemy].getXOnMap() + 1])
				enemy[touchedEnemy].SetMovingDirection(ENEMY_MOVE_RIGHT);	//enemy moved
			else
				enemy[touchedEnemy].SetIsAlive(false);    //enemy died
		}

		// Everything's clear. Move hero
		if (touchedRock == -1 && touchedEnemy == -1 && rockTouchedObject == -1 && enemyTouchedRock == -1 )
			hero.SetMovingDirection(HERO_MOVE_RIGHT);	//hero moved

	}
	else {

	}

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard嚙踝蕭嚙箭嚙磐
	const char KEY_UP    = 0x26; // keyboard嚙磕嚙箭嚙磐
	const char KEY_RIGHT = 0x27; // keyboard嚙糊嚙箭嚙磐
	const char KEY_DOWN  = 0x28; // keyboard嚙磊嚙箭嚙磐
	//if (nChar == KEY_LEFT)
	//	eraser.SetMovingLeft(true);
	//if (nChar == KEY_RIGHT)
	//	eraser.SetMovingRight(true);
	//if (nChar == KEY_UP)
	//	eraser.SetMovingUp(true);
	//if (nChar == KEY_DOWN)
	//	eraser.SetMovingDown(true);
	switch (nChar) {
	case KEY_UP:
		HeroWantToMove(HERO_MOVE_UP);
		break;
	case KEY_DOWN:
		HeroWantToMove(HERO_MOVE_DOWN);
		break;
	case KEY_LEFT:
		HeroWantToMove(HERO_MOVE_LEFT);
		break;
	case KEY_RIGHT:
		HeroWantToMove(HERO_MOVE_RIGHT);
		break;
	default:
		break;
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard嚙踝蕭嚙箭嚙磐
	const char KEY_UP    = 0x26; // keyboard嚙磕嚙箭嚙磐
	const char KEY_RIGHT = 0x27; // keyboard嚙糊嚙箭嚙磐
	const char KEY_DOWN  = 0x28; // keyboard嚙磊嚙箭嚙磐
	//if (nChar == KEY_LEFT)
	//	eraser.SetMovingLeft(false);
	//if (nChar == KEY_RIGHT)
	//	eraser.SetMovingRight(false);
	//if (nChar == KEY_UP)
	//	eraser.SetMovingUp(false);
	//if (nChar == KEY_DOWN)
	//	eraser.SetMovingDown(false);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 嚙畿嚙緲嚙複對蕭嚙踝蕭嚙褊作
{
	//eraser.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 嚙畿嚙緲嚙複對蕭嚙踝蕭嚙褊作
{
	//eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 嚙畿嚙緲嚙複對蕭嚙踝蕭嚙褊作
{
	// 嚙磅嚙複。嚙緘嚙瘦嚙豎要嚙畿嚙緲嚙複對蕭嚙踝蕭嚙褊迎蕭嚙豌，嚙篇code嚙箭嚙緻嚙踝蕭
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 嚙畿嚙緲嚙複對蕭嚙踝蕭嚙褊作
{
	//eraser.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 嚙畿嚙緲嚙複對蕭嚙踝蕭嚙褊作
{
	//eraser.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
	gamemap.OnShow();
	//
	//  嚙窯嚙瞇嚙瘦Show嚙諒哨蕭嚙範嚙磊嚙踝蕭嚙緯嚙踝蕭嚙褊伐蕭嚙踟物件的座嚙請，嚙踝蕭嚙褊座嚙請迎蕭嚙線嚙瑾嚙踝蕭嚙踝蕭Move嚙踝蕭嚙羯嚙踝蕭A
	//        嚙稻嚙篁嚙踝蕭嚙踝蕭嚙踝蕭嚙踝蕭嚙編繪嚙誕殷蕭(OnDraw)嚙璀嚙踝蕭嚙踝蕭N嚙罵嚙踝蕭嚙褊，嚙豎起嚙諉會嚙豌怪。嚙踝蕭嚙諉術嚙緙
	//        嚙踝蕭嚙璀Move嚙緣嚙範MVC嚙踝蕭嚙踝蕭Model嚙璀Show嚙緣嚙範View嚙璀嚙踝蕭View嚙踝蕭嚙踝蕭嚙踝蕭嚙瞎odel嚙瘠
	//
	//
	//  嚙皺嚙磕嚙瘢嚙踝蕭嚙誕、嚙踝蕭嚙踝蕭嚙複、嚙緙嚙畿嚙踝蕭嚙締嚙畿嚙線嚙踝蕭嚙踝蕭嚙緙
	//
	//background.ShowBitmap();			// 嚙皺嚙磕嚙瘢嚙踝蕭嚙踝蕭
	help.ShowBitmap();					// 嚙皺嚙磕嚙踝蕭嚙踝蕭嚙踝蕭
	hits_left.ShowBitmap();
	//for (int i=0; i < NUMBALLS; i++)
	//	ball[i].OnShow();				// 嚙皺嚙磕嚙踝蕭i嚙踝蕭嚙緙
	//bball.OnShow();						// 嚙皺嚙磕嚙線嚙踝蕭嚙踝蕭嚙緙
	//eraser.OnShow();					// 嚙皺嚙磕嚙踝蕭嚙締
	//
	//  嚙皺嚙磕嚙踝蕭嚙磕嚙諄右嚙磊嚙踝蕭嚙踝蕭嚙踝蕭嚙踝蕭
	//
	corner.SetTopLeft(0,0);
	corner.ShowBitmap();
	corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	corner.ShowBitmap();

	hero.OnShow();
	princess.OnShow();
	for (int i = 0; i < stg1_rock_count; i++)
		rocks[i].OnShow();
	for (int i = 0; i < stg1_enemy_count; i++)
		enemy[i].OnShow();
}

CGameMap::CGameMap() :x(0), y(0), mh(400), mw(400) {

}

void CGameMap::LoadBitMap() {
	chapter9.LoadBitmap(IDB_MAP);
}
void CGameMap::OnShow() {
	chapter9.SetTopLeft(x, y);
	chapter9.ShowBitmap();
}

}