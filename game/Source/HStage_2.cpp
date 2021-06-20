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

#include "HStage_2.h"


namespace game_framework {
	HStage_2::HStage_2() {
		basicSetup();
	}
	HStage_2::HStage_2(CGameStateRun* mainState) {
		this->mainState = mainState;

		basicSetup();
	}

	void HStage_2::basicSetup() {
		// Set the maximum move steps.
		steps_left = MAX_MOVE_STEPS = STG2_MAX_MOVE_STEP;

		// Set XY offset.
		xOffset = 364;	yOffset = 56;

		// Set StepsDisplay.
		stepsDisplay = new HStepsDisplay(STG2_MAX_MOVE_STEP);

		// Copy the whole map data to father class' 'map' object.
		for (int y = 0; y < 8; y++)
			for (int x = 0; x < 9; x++)
				map[y][x] = stg2_map[y][x];

		// Determine this stage's princess.
		whichPrincess = PRINCESS_CERBERUS;

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

	HStage_2::~HStage_2() {

	}

	void HStage_2::Initialize() {
		vector<vector<int>> init_map =
			vector<vector<int>>(MAX_AVAILABLE_MAP_HEIGHT, vector<int>(MAX_AVAILABLE_MAP_WIDTH, MAPOBJ_MAPEND));

		for (int x = 0; x < 9; x++)
			for (int y = 0; y < 8; y++)
				init_map.at(y).at(x) = stg2_map[y][x];

		HStage::Initialize(init_map, STAGE_3);


	}

	void HStage_2::loadMyBitmap() {
		backgroundImage.AddBitmap(IMAGE_STAGE_2, RGB(0, 1, 0));
	}
}