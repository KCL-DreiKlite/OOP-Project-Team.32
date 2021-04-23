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


namespace game_framework {
	HStage::HStage() {

	}

	HStage::~HStage() {
		delete hero;
		delete princess;
		delete[] rocks;
		delete[] enemies;
		delete key;
		delete lock;

	}

	/*
	In this method, define this stage's map by the passed argument, and
	initialize every Helltaker object (class like HHero, HRock, etc.)
	*/
	void HStage::Initialize(vector<vector<int>> init_map) {
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

		// Define lock and key if this stage need that
		if (hasLock) {
			key->Initialize();
			lock->Initialize();
		}

	}

	/*
	When called, I'll not only add my bitmap, but also other objects' bitmaps.
	*/
	void HStage::LoadBitmap(int whichPrincess) {
		loadMyBitmap();
		loadOtherBitmaps(whichPrincess);
	}

	void HStage::loadMyBitmap() {

	}

	void HStage::loadOtherBitmaps(int whichPrincess) {
		// Load hero's bitmap
		hero->LoadBitmap();

		// Load princess' bitmap
		princess->LoadBitmap(whichPrincess);

		// Load rocks' bitmap
		for (int r = 0; r < rocksCount; r++)
			rocks->at(r).LoadBitmap(getRandom(1, 3));

		// Load enemies' bitmap
		for (int e = 0; e < rocksCount; e++)
			enemies->at(e).LoadBitmap();

	}

	void HStage::OnShow() {
		hero->OnShow();
		princess->OnMove();
		for (int r = 0; r < rocksCount; r++)
			rocks->at(r).OnShow();
		for (int e = 0; e < enemiesCount; e++)
			enemies->at(e).OnShow();
		if (hasLock) {
			key->OnShow();
			lock->OnShow();
		}
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
