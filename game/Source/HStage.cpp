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
				switch (objectInMap(x, y)) {
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
					if (hasLock)
						key->setXYOnMap(x, y);
					break;
				case MAPOBJ_LOCK:
					if (hasLock)
						lock->setXYOnMap(x, y);
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
		map = init_map;

		// Initialize StepsDisplay.
		stepsDisplay->Initialize(0, 0);

		// Call each object's Initialize()
		int rc = 0, ec = 0;
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				switch (objectInMap(x, y)) {
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
					if (hasLock)
						key->Initialize(x, y, xOffset, yOffset, objectWidth);
					break;
				case MAPOBJ_LOCK:
					if (hasLock)
						lock->Initialize(x, y, xOffset, yOffset, objectWidth);
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
		if (hasLock) {
			key->LoadBitmap();
			lock->LoadBitmap();
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
		if (hasLock) {
			key->OnShow();
			lock->OnShow();
		}

	}

	void HStage::HeroWantToMove(char direction) {
		// Check if hero touched princess
		const int px = princess->getXOnMap(), py = princess->getYOnMap();
		const int hx = hero->getXOnMap(), hy = hero->getYOnMap();
		const int kx = key->getXOnMap(), ky = key->getYOnMap();
		const int lx = lock->getXOnMap(), ly = lock->getYOnMap();

		if (stepsDisplay->getCurrentSteps() <= 0) {
			RestartStage();
			return;
		}

		// 4 steps to move hero:
		// 1. Check if hero want to crash the edge
		// 2. Check if hero touched the rock. If so, then move rock
		// 3. Check if hero touched princess. If so, then game over
		// 4. Check if hero touched the enemy. If so, then move enemy
		// 5. If non of these conditions is true, then move hero.

		if (direction == HERO_MOVE_UP) {
			// Check if hero want to crash the edge
			if (!map[hy - 1][hx])
				return;

			// Check if hero touched the rock
			int touchedRock = -1;
			int rockTouchedObject = -1;
			for (int i = 0; i < rocksCount; i++) {
				const int rx = rocks->at(i).getXOnMap(), ry = rocks->at(i).getYOnMap();
				if (hx == rx && hy - 1 == ry) {
					touchedRock = i;
					// Check if the rock touched the enemy
					for (int i = 0; i < enemiesCount; i++) {
						const int ex = enemies->at(i).getXOnMap(), ey = enemies->at(i).getYOnMap();
						if (rx == ex && ry - 1 == ey) {
							touchedRock = -1;
							rockTouchedObject = 1;
							break;
						}
					}
					// Check if the rock touched the rock
					for (int j = 0; j < rocksCount; j++) {
						const int rx0 = rocks->at(j).getXOnMap(), ry0 = rocks->at(j).getYOnMap();
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
					// Check if the rock touched the key
					if (rx == kx && ry - 1 == ky) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
					// Check if the rock touched the lock
					if (rx == lx && ry - 1 == ly) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
					break;
				}
			}
			if (touchedRock != -1) {
				if (map[rocks->at(touchedRock).getYOnMap() - 1][rocks->at(touchedRock).getXOnMap()]) {
					rocks->at(touchedRock).SetMovingDirection(ROCK_MOVE_UP);	//rock moved
					hero->SetHeroMoved();  //consume steps
				}
			}

			// Check if hero touched princess
			else if (hx == px && hy - 1 == py) {
				//CAudio::Instance()->Stop(AUDIO_NTUT);
				//GotoGameState(GAME_STATE_OVER);
				mainState->StageClear();
			}

			// Check if hero touched enemy
			int touchedEnemy = -1;
			int enemyTouchedRock = -1;
			for (int i = 0; i < enemiesCount; i++) {
				const int ex = enemies->at(i).getXOnMap(), ey = enemies->at(i).getYOnMap();
				if (hx == ex && hy - 1 == ey) {
					touchedEnemy = i;
					// Check if the enemy touched the rock
					for (int i = 0; i < rocksCount; i++) {
						const int rx = rocks->at(i).getXOnMap(), ry = rocks->at(i).getYOnMap();
						if (ex == rx && ey - 1 == ry) {
							enemies->at(touchedEnemy).SetIsAlive(false);
							touchedEnemy = -1;
							enemyTouchedRock = 1;
							hero->SetHeroMoved();  //consume steps
							break;
						}
					}
					break;
				}
			}
			if (touchedEnemy != -1) {
				if (map[enemies->at(touchedEnemy).getYOnMap() - 1][enemies->at(touchedEnemy).getXOnMap()]) {
					enemies->at(touchedEnemy).SetMovingDirection(ENEMY_MOVE_UP);	//enemy moved
					hero->SetHeroMoved();  //consume steps
				}
				else {
					enemies->at(touchedEnemy).SetIsAlive(false);
					hero->SetHeroMoved();  //consume steps
				}
			}

			// Check if hero touched the key
			if (hx == kx && hy - 1 == ky) {
				key->SetIsAlive(false);
			}
			// Check if hero touched the lock
			int touchedLock = -1;
			if (hx == lx && hy - 1 == ly) {
				if (!key->IsAlive()){
					lock->SetIsAlive(false);
				}
				else {
					touchedLock = 1;
				}
			}

			// Everything's clear. Move hero
			if (touchedRock == -1 && touchedEnemy == -1 && rockTouchedObject == -1 && enemyTouchedRock == -1 && touchedLock == -1) {
				hero->SetMovingDirection(HERO_MOVE_UP);	//hero moved
				hero->SetHeroMoved();  //consume steps
			}
		}
		else if (direction == HERO_MOVE_DOWN) {
			// Check if hero want to crash the edge
			if (!map[hy + 1][hx])
				return;

			// Check if hero touched the rock
			int touchedRock = -1;
			int rockTouchedObject = -1;
			for (int i = 0; i < rocksCount; i++) {
				const int rx = rocks->at(i).getXOnMap(), ry = rocks->at(i).getYOnMap();
				if (hx == rx && hy + 1 == ry) {
					touchedRock = i;
					// Check if the rock touched the enemy
					for (int i = 0; i < enemiesCount; i++) {
						const int ex = enemies->at(i).getXOnMap(), ey = enemies->at(i).getYOnMap();
						if (rx == ex && ry + 1 == ey) {
							touchedRock = -1;
							rockTouchedObject = 1;
							break;
						}
					}
					// Check if the rock touched the rock
					for (int j = 0; j < rocksCount; j++) {
						const int rx0 = rocks->at(j).getXOnMap(), ry0 = rocks->at(j).getYOnMap();
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
					// Check if the rock touched the key
					if (rx == kx && ry + 1 == ky) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
					// Check if the rock touched the lock
					if (rx == lx && ry + 1 == ly) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
					break;
				}
			}
			if (touchedRock != -1) {
				if (map[rocks->at(touchedRock).getYOnMap() + 1][rocks->at(touchedRock).getXOnMap()]) {
					rocks->at(touchedRock).SetMovingDirection(ROCK_MOVE_DOWN);	//rock moved
					hero->SetHeroMoved();  //consume steps
				}
			}

			// Check if hero touched princess
			else if (hx == px && hy + 1 == py) {

			}

			// Check if hero touched enemy
			int touchedEnemy = -1;
			int enemyTouchedRock = -1;
			for (int i = 0; i < enemiesCount; i++) {
				const int ex = enemies->at(i).getXOnMap(), ey = enemies->at(i).getYOnMap();
				if (hx == ex && hy + 1 == ey) {
					touchedEnemy = i;
					// Check if the enemy touched the rock
					for (int i = 0; i < rocksCount; i++) {
						const int rx = rocks->at(i).getXOnMap(), ry = rocks->at(i).getYOnMap();
						if (ex == rx && ey + 1 == ry) {
							enemies->at(touchedEnemy).SetIsAlive(false);
							touchedEnemy = -1;
							enemyTouchedRock = 1;
							hero->SetHeroMoved();  //consume steps
							break;
						}
					}
					break;
				}
			}
			if (touchedEnemy != -1) {
				if (map[enemies->at(touchedEnemy).getYOnMap() + 1][enemies->at(touchedEnemy).getXOnMap()]) {
					enemies->at(touchedEnemy).SetMovingDirection(ENEMY_MOVE_DOWN);	//enemy moved
					hero->SetHeroMoved();  //consume steps
				}
				else {
					enemies->at(touchedEnemy).SetIsAlive(false);
					hero->SetHeroMoved();  //consume steps
				}
			}

			// Check if hero touched the key
			if (hx == kx && hy + 1 == ky) {
				key->SetIsAlive(false);
			}
			// Check if hero touched the lock
			int touchedLock = -1;
			if (hx == lx && hy + 1 == ly) {
				if (!key->IsAlive()) {
					lock->SetIsAlive(false);
				}
				else {
					touchedLock = 1;
				}
			}

			// Everything's clear. Move hero
			if (touchedRock == -1 && touchedEnemy == -1 && rockTouchedObject == -1 && enemyTouchedRock == -1 && touchedLock == -1) {
				hero->SetMovingDirection(HERO_MOVE_DOWN);	//hero moved
				hero->SetHeroMoved();  //consume steps
			}
		}
		else if (direction == HERO_MOVE_LEFT) {
			// Check if hero want to crash the edge
			if (!map[hy][hx - 1])
				return;

			// Check if hero touched the rock
			int touchedRock = -1;
			int rockTouchedObject = -1;
			for (int i = 0; i < rocksCount; i++) {
				const int rx = rocks->at(i).getXOnMap(), ry = rocks->at(i).getYOnMap();
				if (hx - 1 == rx && hy == ry) {
					touchedRock = i;
					// Check if the rock touched the enemy
					for (int i = 0; i < enemiesCount; i++) {
						const int ex = enemies->at(i).getXOnMap(), ey = enemies->at(i).getYOnMap();
						if (rx - 1 == ex && ry== ey) {
							touchedRock = -1;
							rockTouchedObject = 1;
							break;
						}
					}
					// Check if the rock touched the rock
					for (int j = 0; j < rocksCount; j++) {
						const int rx0 = rocks->at(j).getXOnMap(), ry0 = rocks->at(j).getYOnMap();
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
					// Check if the rock touched the key
					if (rx - 1 == kx && ry == ky) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
					// Check if the rock touched the lock
					if (rx - 1 == lx && ry == ly) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
					break;
				}
			}
			if (touchedRock != -1) {
				if (map[rocks->at(touchedRock).getYOnMap()][rocks->at(touchedRock).getXOnMap() - 1]) {
					rocks->at(touchedRock).SetMovingDirection(ROCK_MOVE_LEFT);	//rock moved
					hero->SetHeroMoved();  //consume steps
				}
			}

			// Check if hero touched princess
			else if (hx - 1 == px && hy == py) {
				//CAudio::Instance()->Stop(AUDIO_NTUT);
				//GotoGameState(GAME_STATE_OVER);
				mainState->StageClear();
			}

			// Check if hero touched enemy
			int touchedEnemy = -1;
			int enemyTouchedRock = -1;
			for (int i = 0; i < enemiesCount; i++) {
				const int ex = enemies->at(i).getXOnMap(), ey = enemies->at(i).getYOnMap();
				if (hx - 1 == ex && hy == ey) {
					touchedEnemy = i;
					// Check if the enemy touched the rock
					for (int i = 0; i < rocksCount; i++) {
						const int rx = rocks->at(i).getXOnMap(), ry = rocks->at(i).getYOnMap();
						if (ex - 1 == rx && ey == ry) {
							enemies->at(touchedEnemy).SetIsAlive(false);
							touchedEnemy = -1;
							enemyTouchedRock = 1;
							hero->SetHeroMoved();  //consume steps
							break;
						}
					}
					break;
				}
			}
			if (touchedEnemy != -1) {
				if (map[enemies->at(touchedEnemy).getYOnMap()][enemies->at(touchedEnemy).getXOnMap() - 1]) {
					enemies->at(touchedEnemy).SetMovingDirection(ENEMY_MOVE_LEFT);	//enemy moved
					hero->SetHeroMoved();  //consume steps
				}
				else {
					enemies->at(touchedEnemy).SetIsAlive(false);
					hero->SetHeroMoved();  //consume steps
				}
			}

			// Check if hero touched the key
			if (hx - 1 == kx && hy == ky) {
				key->SetIsAlive(false);
			}
			// Check if hero touched the lock
			int touchedLock = -1;
			if (hx - 1 == lx && hy == ly) {
				if (!key->IsAlive()){
					lock->SetIsAlive(false);
				}
				else {
					touchedLock = 1;
				}
			}

			// Everything's clear. Move hero
			if (touchedRock == -1 && touchedEnemy == -1 && rockTouchedObject == -1 && enemyTouchedRock == -1 && touchedLock == -1) {
				hero->SetMovingDirection(HERO_MOVE_LEFT);	//hero moved
				hero->SetHeroMoved();  //consume steps
			}
		}
		else if (direction == HERO_MOVE_RIGHT) {
			// Check if hero want to crash the edge
			if (!map[hy][hx + 1])
				return;

			// Check if hero touched the rock
			int touchedRock = -1;
			int rockTouchedObject = -1;
			for (int i = 0; i < rocksCount; i++) {
				const int rx = rocks->at(i).getXOnMap(), ry = rocks->at(i).getYOnMap();
				if (hx + 1 == rx && hy == ry) {
					touchedRock = i;
					// Check if the rock touched the enemy
					for (int i = 0; i < enemiesCount; i++) {
						const int ex = enemies->at(i).getXOnMap(), ey = enemies->at(i).getYOnMap();
						if (rx + 1 == ex && ry == ey) {
							touchedRock = -1;
							rockTouchedObject = 1;
							break;
						}
					}
					// Check if the rock touched the rock
					for (int j = 0; j < rocksCount; j++) {
						const int rx0 = rocks->at(j).getXOnMap(), ry0 = rocks->at(j).getYOnMap();
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
					// Check if the rock touched the key
					if (rx + 1 == kx && ry == ky) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
					// Check if the rock touched the lock
					if (rx + 1 == lx && ry == ly) {
						touchedRock = -1;
						rockTouchedObject = 1;
						break;
					}
					break;
				}
			}
			if (touchedRock != -1) {
				if (map[rocks->at(touchedRock).getYOnMap()][rocks->at(touchedRock).getXOnMap() + 1]) {
					rocks->at(touchedRock).SetMovingDirection(ROCK_MOVE_RIGHT);	//rock moved
					hero->SetHeroMoved();  //consume steps
				}
			}

			// Check if hero touched princess
			else if (hx + 1 == px && hy == py) {
				//CAudio::Instance()->Stop(AUDIO_NTUT);
				//GotoGameState(GAME_STATE_OVER);
				mainState->StageClear();
			}

			// Check if hero touched enemy
			int touchedEnemy = -1;
			int enemyTouchedRock = -1;
			for (int i = 0; i < enemiesCount; i++) {
				const int ex = enemies->at(i).getXOnMap(), ey = enemies->at(i).getYOnMap();
				if (hx + 1 == ex && hy == ey) {
					touchedEnemy = i;
					// Check if the enemy touched the rock
					for (int i = 0; i < rocksCount; i++) {
						const int rx = rocks->at(i).getXOnMap(), ry = rocks->at(i).getYOnMap();
						if (ex + 1 == rx && ey == ry) {
							enemies->at(touchedEnemy).SetIsAlive(false);
							touchedEnemy = -1;
							enemyTouchedRock = 1;
							hero->SetHeroMoved();  //consume steps
							break;
						}
					}
					break;
				}
			}
			if (touchedEnemy != -1) {
				if (map[enemies->at(touchedEnemy).getYOnMap()][enemies->at(touchedEnemy).getXOnMap() + 1]) {
					enemies->at(touchedEnemy).SetMovingDirection(ENEMY_MOVE_RIGHT);	//enemy moved
					hero->SetHeroMoved();  //consume steps
				}
				else {
					enemies->at(touchedEnemy).SetIsAlive(false);
					hero->SetHeroMoved();  //consume steps
				}
			}

			// Check if hero touched the key
			if (hx + 1 == kx && hy == ky) {
				key->SetIsAlive(false);
			}
			// Check if hero touched the lock
			int touchedLock = -1;
			if (hx + 1 == lx && hy == ly) {
				if (!key->IsAlive()) {
					lock->SetIsAlive(false);
				}
				else {
					touchedLock = 1;
				}
			}

			// Everything's clear. Move hero
			if (touchedRock == -1 && touchedEnemy == -1 && rockTouchedObject == -1 && enemyTouchedRock == -1 && touchedLock == -1) {
				hero->SetMovingDirection(HERO_MOVE_RIGHT);	//hero moved
				hero->SetHeroMoved();  //consume steps
			}
		}
		else {

		}

		if (hero->heroIsMoved()) {
			stepsDisplay->reduceStep();
		}
	}

	void HStage::quickPass() {
		for (int i = 0; i < rocksCount; i++)
			rocks->at(i).SetIsAlive(false);
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
		key->OnMove();
		lock->OnMove();

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
	HKey* HStage::getKey() { return key; }
	HLock* HStage::getLock() { return lock; }

}
