#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include "mygame.h"

#include <vector>
#include <stdlib.h>

#include "HStepsDisplay.h"

#include "HHero.h"
#include "HPrincess.h"
#include "HRock.h"
#include "HEnemy.h"
#include "HKey.h"
#include "HLock.h"

#include "HStage.h"


namespace game_framework {
	HStage::HStage() {
		basicSetup();
	}

	HStage::HStage(CGameStateRun* mainState) {
		this->mainState = mainState;

		basicSetup();
	}

	HStage::HStage(CGameStateStage_2* mainState2) {
		this->mainState2 = mainState2;

		basicSetup();
	}

	void HStage::basicSetup() {
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

	void HStage::RestartStage() {
		// Reset current move steps.
		steps_left = MAX_MOVE_STEPS;

		// Reset dynamic map to stage map.
		map = vector<vector<int>>(STAGE_MAP);

		// Reset steps display.
		stepsDisplay->resetCurrentSteps();

		// Reset key & lock's alive status.
		if (hasLock) {
			key->SetIsAlive(true);
			lock->SetIsAlive(true);
		}

		// Reset enemies' alive status.
		for (int ec = 0; ec < enemiesCount; ec++)
			enemies->at(ec).SetIsAlive(true);

		// Reset every objects' location.
		for (int x = 0, rc = 0, ec = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				switch (getMapObjNum(x, y)) {
				case MAPOBJ_MAPEND:
				case MAPOBJ_EDGE:
				case MAPOBJ_MOVABLE:
					continue;
				case MAPOBJ_HERO:
					hero->setXYOnMap(x, y);
					hero->SetHeroDirectionBitmap(HERO_FACING_RIGHT);
					break;
				case MAPOBJ_PRINCESS:
					princess->setXYOnMap(x, y);
					break;
				case MAPOBJ_ROCK:
					rocks->at(rc++).setXYOnMap(x, y);
					break;
				case MAPOBJ_ENEMY:
					enemies->at(ec++).setXYOnMap(x, y);
					break;
				case MAPOBJ_KEY:
					key->setXYOnMap(x, y);
					//hasLock = true;
					break;
				case MAPOBJ_LOCK:
					lock->setXYOnMap(x, y);
					//hasLock = true;
					break;
				default:
					break;
				}
			}
		}

		// Reset every objects' alive status (if exist).
		for (int rc = 0; rc < rocksCount; rc++)
			rocks->at(rc).SetIsAlive(true);
		for (int ec = 0; ec < enemiesCount; ec++)
			enemies->at(ec).SetIsAlive(true);
		
	}

	/*
	In this method, define this stage's map by the passed argument, and
	initialize every Helltaker object (class like HHero, HRock, etc.)
	*/
	void HStage::Initialize(vector<vector<int>> init_map) {
		// Load stage map.
		STAGE_MAP = init_map;

		// Copy stage map to dynamic map.
		map = vector<vector<int>>(STAGE_MAP);

		// Initialize StepsDisplay.
		stepsDisplay->Initialize(0, 0);

		// Call each object's Initialize()
		int rc = 0, ec = 0;
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				switch (getMapObjNum(x, y)) {
				case MAPOBJ_MAPEND:
				case MAPOBJ_EDGE:
				case MAPOBJ_MOVABLE:
					continue;
				case MAPOBJ_HERO:
					hero->Initialize(x, y, xOffset, yOffset, objectWidth);
					break;
				case MAPOBJ_PRINCESS:
					princess->Initialize(x, y, xOffset, yOffset, objectWidth);
					break;
				case MAPOBJ_ROCK:
					rocks->at(rc++).Initialize(x, y, xOffset, yOffset, objectWidth);
					break;
				case MAPOBJ_ENEMY:
					enemies->at(ec++).Initialize(x, y, xOffset, yOffset, objectWidth);
					break;
				case MAPOBJ_KEY:
					key->Initialize(x, y, xOffset, yOffset, objectWidth);
					//hasLock = true;
					break;
				case MAPOBJ_LOCK:
					lock->Initialize(x, y, xOffset, yOffset, objectWidth);
					//hasLock = true;
					break;
				default:
					break;
				}
			}
		}

		// i'm too lazy so add this after initialization.
		RestartStage();
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
		// Load stepsDisplay's beginning bitmap
		stepsDisplay->LoadBitmap();

		// Load hero's bitmap
		hero->LoadBitmap();

		// Load princess' bitmap
		princess->LoadBitmap(whichPrincess);

		// Load rocks' bitmap
		for (int r = 0; r < rocksCount; r++)
			rocks->at(r).LoadBitmap(r%3);

		// Load enemies' bitmap
		for (int e = 0; e < enemiesCount; e++)
			enemies->at(e).LoadBitmap();

		// Load lock and key's bitmap
		//if (hasLock) {
		//	key->LoadBitmap();
		//	lock->LoadBitmap();
		//}

		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				if (getMapObjNum(x, y) == MAPOBJ_KEY) {
					key->LoadBitmap();
				}
				else if (getMapObjNum(x, y) == MAPOBJ_LOCK) {
					lock->LoadBitmap();
				}
			}
		}
	}

	void HStage::OnShow() {
		backgroundImage.SetTopLeft(0, 0);
		backgroundImage.OnShow();

		stepsDisplay->OnShow();

		hero->OnShow();
		princess->OnShow();
		for (int r = 0; r < rocksCount; r++)
			rocks->at(r).OnShow();
		for (int e = 0; e < enemiesCount; e++)
			enemies->at(e).OnShow();
		//if (hasLock) {
		//	key->OnShow();
		//	lock->OnShow();
		//}
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				if (getMapObjNum(x, y) == MAPOBJ_KEY) {
					key->OnShow();
				}
				else if (getMapObjNum(x, y) == MAPOBJ_LOCK) {
					lock->OnShow();
				}
			}
		}

	}

	void HStage::HeroWantToMove(char direction) {

		// Check remain steps.
		if (stepsDisplay->getCurrentSteps() <= 0) {

			RestartStage();
			return;
		}

		// Start move things.
		const int hx = hero->getXOnMap(), hy = hero->getYOnMap();

		HeroMoveType hmt = HMT_NONE;

		int xConditionLength = 0, yConditionLength = 0;
		switch (direction) {
		case HERO_MOVE_UP:
			yConditionLength = -1;	break;
		case HERO_MOVE_DOWN:
			yConditionLength = 1;	break;
		case HERO_MOVE_LEFT:
			xConditionLength = -1;	break;
		case HERO_MOVE_RIGHT:
			xConditionLength = 1;	break;
		default:
			break;
		}

		int thingOnTheWay = getMapObjNum(hx + xConditionLength, hy + yConditionLength);
		if (thingOnTheWay == MAPOBJ_MOVABLE) {
			hero->SetMovingDirection(direction);
			hmt = HMT_PLAINMOVE;
		}
		else if (thingOnTheWay == MAPOBJ_EDGE) {
			hmt = HMT_NONE;
		}
		else if (thingOnTheWay == MAPOBJ_ROCK) {
			if (getMapObjNum(hx + xConditionLength * 2, hy + yConditionLength * 2) == MAPOBJ_MOVABLE) {
				((HRock*)getMapObject(hx + xConditionLength, hy + yConditionLength))->SetMovingDirection(direction);
				hmt = HMT_KICKROCK_MOVABLE;
			}
			else {
				hmt = HMT_NONE; //HMT_KICKROCK_UNMOVABLE;
			}
		}
		else if (thingOnTheWay == MAPOBJ_ENEMY) {
			if (getMapObjNum(hx + xConditionLength * 2, hy + yConditionLength * 2) == MAPOBJ_MOVABLE) {
				((HEnemy*)getMapObject(hx + xConditionLength, hy + yConditionLength))->SetMovingDirection(direction);
				hmt = HMT_KICKENEMY;
			}
			else {
				((HEnemy*)getMapObject(hx + xConditionLength, hy + yConditionLength))->SetIsAlive(false);
				hmt = HMT_KILLENEMY;
			}
		}
		else if (thingOnTheWay == MAPOBJ_KEY) {
			hero->SetMovingDirection(direction);
			key->SetIsAlive(false);
			hmt = HMT_PICKKEY;
		}
		else if (thingOnTheWay == MAPOBJ_LOCK) {
			if (!key->IsAlive()) {		// Hero got the key
				hero->SetMovingDirection(direction);
				lock->SetIsAlive(false);
				hmt = HMT_UNLOCK_WITHKEY;
			}
			else {						// hero don't have key
				hmt = HMT_UNLOCK_NOKEY;
			}
		}
		else if (thingOnTheWay == MAPOBJ_PRINCESS) {
			mainState->StageClear();
			hmt = HMT_MEETPRINCESS;
		}
		else if (false/*thingOnTheWay == MAPOBJ_PRINCESS*/) {
			mainState2->StageClear();
			hmt = HMT_MEETPRINCESS;
		}
		else {}

		// Update StepsDisplay.
		if (hmt != HMT_NONE) {
			stepsDisplay->reduceStep();
		}

		// Play sound effect.
		switch (hmt) {
		case HMT_PLAINMOVE:
			CAudio::Instance()->Play(AUDIO_CHARACTER_MOVE);
			break;
		case HMT_KICKROCK_MOVABLE:
			CAudio::Instance()->Play(AUDIO_ROCK_KICKED);
			CAudio::Instance()->Play(AUDIO_ROCK_MOVED);
			break;
		case HMT_KICKROCK_UNMOVABLE:
			CAudio::Instance()->Play(AUDIO_ROCK_KICKED);
			break;
		case HMT_KICKENEMY:
			CAudio::Instance()->Play(AUDIO_ENEMY_KICK);
			break;
		case HMT_KILLENEMY:
			CAudio::Instance()->Play(AUDIO_ENEMY_KILL);
			break;
		case HMT_PICKKEY:
			CAudio::Instance()->Play(AUDIO_PICKKEY);
			break;
		case HMT_UNLOCK_WITHKEY:
			CAudio::Instance()->Play(AUDIO_LOCK_WITHKEY);
			break;
		case HMT_UNLOCK_NOKEY:
			CAudio::Instance()->Play(AUDIO_LOCK_NOKEY);
			break;
		case HMT_MEETPRINCESS:
			break;
		default:
			break;

		}
	}

	void HStage::updateDynamicMap() {
		const int whateverItIs = -20;

		// First, set all map object to whatever it is. Except EDGE and MAPEND.
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				if (getMapObjNum(x, y) == MAPOBJ_MAPEND ||
					getMapObjNum(x, y) == MAPOBJ_EDGE)
					continue;
				getMapObjNum(x, y) = whateverItIs;
			}
		}

		// Next, assign every single object into dynamic map.
		getMapObjNum(hero->getXOnMap(), hero->getYOnMap()) = MAPOBJ_HERO;
		getMapObjNum(princess->getXOnMap(), princess->getYOnMap()) = MAPOBJ_PRINCESS;
		for (int rc = 0; rc < rocksCount; rc++) {
			if (rocks->at(rc).IsAlive())
				getMapObjNum(rocks->at(rc).getXOnMap(), rocks->at(rc).getYOnMap()) = MAPOBJ_ROCK;
			else
				getMapObjNum(rocks->at(rc).getXOnMap(), rocks->at(rc).getYOnMap()) = MAPOBJ_MOVABLE;
		}
		for (int ec = 0; ec < enemiesCount; ec++) {
			if (enemies->at(ec).IsAlive())
				getMapObjNum(enemies->at(ec).getXOnMap(), enemies->at(ec).getYOnMap()) = MAPOBJ_ENEMY;
			else
				getMapObjNum(enemies->at(ec).getXOnMap(), enemies->at(ec).getYOnMap()) = MAPOBJ_MOVABLE;
		}

		//here need to be revised
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				if (getMapObjNum(x, y) == MAPOBJ_KEY || getMapObjNum(x, y) == MAPOBJ_LOCK) {
					if (key->IsAlive())
						getMapObjNum(key->getXOnMap(), key->getYOnMap()) = MAPOBJ_KEY;
					else
						getMapObjNum(key->getXOnMap(), key->getYOnMap()) = MAPOBJ_MOVABLE;

					if (lock->IsAlive())
						getMapObjNum(lock->getXOnMap(), lock->getYOnMap()) = MAPOBJ_LOCK;
					else
						getMapObjNum(lock->getXOnMap(), lock->getYOnMap()) = MAPOBJ_MOVABLE;
				}
			}
		}

		// And finally, remember those whatever it is stuff? Right,
		// now replace them to MOVABLE.
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				if (getMapObjNum(x, y) == whateverItIs)
					getMapObjNum(x, y) = MAPOBJ_MOVABLE;
			}
		}
	}

	void HStage::OnMove() {
		backgroundImage.OnMove();

		stepsDisplay->OnMove();

		hero->OnMove();
		princess->OnMove();
		for (int i = 0; i < rocksCount; i++)
			rocks->at(i).OnMove();
		for (int i = 0; i < enemiesCount; i++)
			enemies->at(i).OnMove();
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				if (getMapObjNum(x, y) == MAPOBJ_KEY || getMapObjNum(x, y) == MAPOBJ_LOCK) {
					key->OnMove();
					lock->OnMove();
				}
			}
		}
		updateDynamicMap();
	}

	void HStage::quickPass() {
		for (int i = 0; i < rocksCount; i++)
			rocks->at(i).SetIsAlive(false);
	}

	void HStage::setXY(int nx, int ny) {
		x = nx; y = ny;
	}

	const int HStage::findObjectsX(int xInMap) { return x + xInMap * objectWidth; }
	const int HStage::findObjectsY(int yInMap) { return y + yInMap * objectWidth; }

	HMapObject* HStage::getMapObject(int xOnMap, int yOnMap) {
		if (getMapObjNum(xOnMap, yOnMap) == MAPOBJ_MAPEND ||
			getMapObjNum(xOnMap, yOnMap) == MAPOBJ_EDGE)
			return NULL;

		if (isSameLocation(hero->, xOnMap, yOnMap))
			return hero;

		if (isSameLocation(princess->, xOnMap, yOnMap))
			return princess;
		
		for (int rc = 0; rc < rocksCount; rc++)
			if (isSameLocation(rocks->at(rc)., xOnMap, yOnMap))
				return &(rocks->at(rc));

		for (int ec = 0; ec < enemiesCount; ec++)
			if (isSameLocation(enemies->at(ec)., xOnMap, yOnMap))
				return &(enemies->at(ec));

		if (isSameLocation(key->, xOnMap, yOnMap))
			return key;

		if (isSameLocation(lock->, xOnMap, yOnMap))
			return lock;

		return NULL;
	}

	const int HStage::getX() { return x; }
	const int HStage::getY() { return y; }

	const vector<vector<int>>* HStage::getMap() { return &map; }

	//const int HStage::getWidth() { return map_width * objectWidth; }
	//const int HStage::getHeight() { return map_height * objectWidth; }

	HHero* HStage::getHero() { return hero; }
	HPrincess* HStage::getPrincess() { return princess; }
	vector<HRock>* HStage::getRocks() { return rocks; }
	vector<HEnemy>* HStage::getEnemies() { return enemies; }
	HKey* HStage::getKey() { return key; }
	HLock* HStage::getLock() { return lock; }

}
