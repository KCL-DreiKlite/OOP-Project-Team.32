#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include <vector>
#include <stdlib.h>

#include "mygame.h"

#include "HStepsDisplay.h"

#include "HHero.h"
#include "HPrincess.h"
#include "HRock.h"
#include "HEnemy.h"
#include "HKey.h"
#include "HLock.h"
#include "HStage.h"

#include "HStage_3.h"


namespace game_framework {
	HStage_3::HStage_3() {
		basicSetup();
	}
	HStage_3::HStage_3(CGameStateRun* mainState) {
		this->mainState = mainState;

		basicSetup();
	}

	void HStage_3::basicSetup() {
		// Set the maximum move steps.
		steps_left = MAX_MOVE_STEPS = STG3_MAX_MOVE_STEP;

		// Set XY offset.
		xOffset = 390;	yOffset = -50;

		// Set StepsDisplay.
		stepsDisplay = new HStepsDisplay(STG3_MAX_MOVE_STEP);

		// Copy the whole map data to father class' 'map' object.
		for (int y = 0; y < 10; y++)
			for (int x = 0; x < 9; x++)
				map[y][x] = stg3_map[y][x];

		// Determine this stage's princess.
		whichPrincess = PRINCESS_AZAZEL;

		// Find the end of the map and assign height and width.
		for (int i = 0; i < MAX_AVAILABLE_MAP_WIDTH; i++)
			if (getMapObjNum(i, 0) == MAPOBJ_MAPEND) {
				map_width = i;
				break;
			}
		for (int i = 0; i < MAX_AVAILABLE_MAP_HEIGHT; i++)
			if (getMapObjNum(0, i) == MAPOBJ_MAPEND) {
				map_height = i;
				break;
			}

		// Find out how many rocks and enemies in map.
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				if (getMapObjNum(x, y) == MAPOBJ_ROCK) {
					rocksCount++;
				}
				else if (getMapObjNum(x, y) == MAPOBJ_ENEMY) {
					enemiesCount++;
				}
			}
		}

		// Initialize 'rocks' & 'enemies' vectors.
		rocks = new vector<HRock>(rocksCount, HRock());
		enemies = new vector<HEnemy>(enemiesCount, HEnemy());
	}

	HStage_3::~HStage_3() {

	}

	void HStage_3::Initialize() {
		vector<vector<int>> init_map =
			vector<vector<int>>(MAX_AVAILABLE_MAP_HEIGHT, vector<int>(MAX_AVAILABLE_MAP_WIDTH, MAPOBJ_MAPEND));

		for (int x = 0; x < 9; x++)
			for (int y = 0; y < 10; y++)
				init_map.at(y).at(x) = stg3_map[y][x];

		HStage::Initialize(init_map, STAGE_OVER);


	}

	void HStage_3::loadMyBitmap() {
		backgroundImage.AddBitmap(IMAGE_STAGE_3, RGB(0, 1, 0));
	}
}