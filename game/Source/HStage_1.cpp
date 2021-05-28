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

		// Set the maximum move steps.
		MAX_MOVE_STEPS = STG1_MAX_MOVE_STEP;
		steps_left = MAX_MOVE_STEPS;

		// Copy the whole map data to father class' 'map' object.
		for (int y = 0; y < 9; y++)
			for (int x = 0; x < 11; x++)
				map[y][x] = stg1_map[y][x];

		// Determine this stage's princess.
		whichPrincess = PRINCESS_LUCIFER;

		// Find the end of the map and assign height and width.
		for (int i = 0; i < MAX_AVAILABLE_MAP_WIDTH; i++)
			if (objectInMap(i, 0) == MAPOBJ_MAPEND) {
				map_width = i;
				break;
			}
		for (int i = 0; i < MAX_AVAILABLE_MAP_HEIGHT; i++)
			if (objectInMap(0, i) == MAPOBJ_MAPEND) {
				map_height = i;
				break;
			}

		// Find out how many rocks and enemies in map.
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				if (objectInMap(x, y) == MAPOBJ_ROCK) {
					rocksCount++;
				}
				else if (objectInMap(x, y) == MAPOBJ_ENEMY) {
					enemiesCount++;
				}
			}
		}

		// Initialize 'rocks' & 'enemies' objects.
		rocks = new vector<HRock>(rocksCount, HRock());
		enemies = new vector<HEnemy>(enemiesCount, HEnemy());
	}

	HStage_1::HStage_1(CGameStateRun* mainState) {
		this->mainState = mainState;

		HStage_1();
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
		//backgroundImage.LoadBitmap(".\\Bitmaps\\Chapter 9-1.bmp");
		backgroundImage.AddBitmap(".\\Bitmaps\\Chapter 9-1.bmp", RGB(0, 1, 0));
	}
}