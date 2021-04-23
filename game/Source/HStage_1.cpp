#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include <vector>
#include <stdlib.h>

#include "HHero.h"
#include "HPrincess.h"
#include "HRock.h"
#include "HEnemy.h"
#include "HKey.h"
#include "HLock.h"
#include "HStage.h"

#include "HStage_1.h"

//#include <vector>
//
//#include "HStage.h"

namespace game_framework {
	HStage_1::HStage_1() {
		for (int y = 0; y < 9; y++)
			for (int x = 0; x < 11; x++)
				map[y][x] = stg1_map[y][x];
	}
	HStage_1::~HStage_1() {
		for (int i = 0; i < 9; i++)
			delete[] stg1_map[i];
		delete[] stg1_map;
	}

	void HStage_1::loadMyBitmap() {
		backgroundImage.LoadBitmap(".\\Bitmaps\\Chapter 9-1.bmp");
	}
}