#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include <vector>

#include "HHero.h"
#include "HPrincess.h"
#include "HRock.h"
#include "HEnemy.h"

#include "HStage.h"


namespace game_framework {
	HStage::HStage() {

	}

	/*
	In this method, define this stage's map by the passed argument, and
	initialize every Helltaker object (class like HHero, HRock, etc.)
	*/
	void HStage::Initialize(vector<vector<int>> init_map, int whichPrincess, int whichImage) {
		map = init_map;

		// Find the end of the map
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

		// Find out how many rocks and enemies in map
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

		// Define Hero
		hero->Initialize();

		// Define Princess
		princess->Initialize();


		// Define rocks
		*rocks = vector<HRock>(rocksCount, HRock());
		int cur_rock = 0;
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				if (objectInMap(x, y) == MAPOBJ_ROCK) {
					//rocks->at(cur_rock).Initialize(x, y);
					rocks->at(cur_rock++).Initialize(findObjectsX(x), findObjectsY(y), x, y);
				}
			}
		}

		// Define enemies
		*enemies = vector<HEnemy>(enemiesCount, HEnemy());
		int cur_enem = 0;
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				if (objectInMap(x, y) == MAPOBJ_ENEMY) {
					enemies->at(cur_enem).Initialize(findObjectsX(x), findObjectsY(y), x, y);
				}
			}
		}



	}

	/*
	When called, I'll not only add my bitmap, but also other objects' bitmaps.
	*/
	void HStage::LoadBitmap() {
		
	}

	void HStage::OnShow() {

	}

	void HStage::OnMove() {

	}

	void HStage::setXY(int nx, int ny) {
		x = nx; y = ny;
	}

	int HStage::findObjectsX(int xInMap) { return x + xInMap * objectWidth; }
	int HStage::findObjectsY(int yInMap) { return y + yInMap * objectWidth; }

	int HStage::getX() { return x; }
	int HStage::getY() { return y; }

	HHero* HStage::getHero() { return hero; }
	HPrincess* HStage::getPrincess() { return princess; }
	vector<HRock>* HStage::getRocks() { return rocks; }
	vector<HEnemy>* HStage::getEnemies() { return enemies; }

}
