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
		map.assign(MAX_AVAILABLE_MAP_HEIGHT, vector<int>(MAX_AVAILABLE_MAP_WIDTH, MAPOBJ_MAPEND));
	}

	HStage::~HStage() {
		//delete hero;
		//delete princess;
		//delete[] rocks;
		//delete[] enemies;
		//delete key;
		//delete lock;
		
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

		// Call each object's Initialize()
		int rc = 0, ec = 0;
		rocks = new vector<HRock>(rocksCount, HRock());
		enemies = new vector<HEnemy>(enemiesCount, HEnemy());
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				switch (objectInMap(x, y)) {
				case MAPOBJ_MAPEND:
				case MAPOBJ_EDGE:
				case MAPOBJ_MOVABLE:
					continue;
				case MAPOBJ_HERO:
					hero->Initialize(x, y, objectWidth);
					break;
				case MAPOBJ_PRINCESS:
					princess->Initialize(x, y, objectWidth);
					break;
				case MAPOBJ_ROCK:
					rocks->at(rc++).Initialize(x, y, objectWidth);
					break;
				case MAPOBJ_ENEMY:
					rocks->at(ec++).Initialize(x, y, objectWidth);
					break;
				case MAPOBJ_KEY:
					if (hasLock)
						key->Initialize(x, y, objectWidth);
					break;
				case MAPOBJ_LOCK:
					if (hasLock)
						lock->Initialize(x, y, objectWidth);
					break;
				default:
					break;
				}
			}
		}

		//// Define Hero
		//hero->Initialize();

		//// Define Princess
		//princess->Initialize();


		//// Define rocks
		//*rocks = vector<HRock>(rocksCount, HRock());
		//int cur_rock = 0;
		//for (int x = 0; x < map_width; x++) {
		//	for (int y = 0; y < map_height; y++) {
		//		if (objectInMap(x, y) == MAPOBJ_ROCK) {
		//			//rocks->at(cur_rock).Initialize(x, y);
		//			rocks->at(cur_rock++).Initialize(findObjectsX(x), findObjectsY(y), x, y);
		//		}
		//	}
		//}

		//// Define enemies
		//*enemies = vector<HEnemy>(enemiesCount, HEnemy());
		//int cur_enem = 0;
		//for (int x = 0; x < map_width; x++) {
		//	for (int y = 0; y < map_height; y++) {
		//		if (objectInMap(x, y) == MAPOBJ_ENEMY) {
		//			enemies->at(cur_enem).Initialize(findObjectsX(x), findObjectsY(y), x, y);
		//		}
		//	}
		//}

		//// Define lock and key if this stage need that
		//if (hasLock) {
		//	key->Initialize();
		//	lock->Initialize();
		//}

	}

	/*
	When called, I'll not only add my bitmap, but also other objects' bitmaps.
	*/
	void HStage::LoadBitmap() {
		loadMyBitmap();
		loadOtherBitmaps();
	}

	void HStage::loadMyBitmap() {

	}

	void HStage::loadOtherBitmaps() {
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

		// Load lock and key's bitmap
		if (hasLock) {
			key->LoadBitmap();
			lock->LoadBitmap();
		}
	}

	void HStage::OnShow() {
		hero->OnShow();
		princess->OnShow();
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

	const int HStage::findObjectsX(int xInMap) { return x + xInMap * objectWidth; }
	const int HStage::findObjectsY(int yInMap) { return y + yInMap * objectWidth; }

	const int HStage::getX() { return x; }
	const int HStage::getY() { return y; }

	const vector<vector<int>>* HStage::getMap() { return &map; }

	//const int HStage::getWidth() { return map_width * objectWidth; }
	//const int HStage::getHeight() { return map_height * objectWidth; }

	HHero* HStage::getHero() { return hero; }
	HPrincess* HStage::getPrincess() { return princess; }
	vector<HRock>* HStage::getRocks() { return rocks; }
	vector<HEnemy>* HStage::getEnemies() { return enemies; }

}
