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
		whichPrincess = PRINCESS_LUCIFER;
	}
	HStage_1::~HStage_1() {
		//for (int i = 0; i < 9; i++)
		//	delete[] stg1_map[i];
		//delete[] stg1_map;
	}

	void HStage_1::Initialize() {
		vector<vector<int>> init_map = 
			vector<vector<int>>(MAX_AVAILABLE_MAP_HEIGHT, vector<int>(MAX_AVAILABLE_MAP_WIDTH, MAPOBJ_MAPEND));

		for (int x = 0; x < 11; x++)
			for (int y = 0; y < 9; y++)
				init_map.at(y).at(x) = stg1_map[y][x];

		HStage::Initialize(init_map);


	}

	void HStage_1::loadMyBitmap() {
		backgroundImage.LoadBitmap(".\\Bitmaps\\Chapter 9-1.bmp");
	}
}