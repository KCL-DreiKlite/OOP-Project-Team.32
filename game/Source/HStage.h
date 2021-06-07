
#include "HStepsDisplay.h"

namespace game_framework {

#ifndef _HSTAGE_H_
#define _HSTAGE_H_


#define MAX_AVAILABLE_MAP_WIDTH		20
#define MAX_AVAILABLE_MAP_HEIGHT	20

#define OBJECT_MOVE_UP				'u'
#define OBJECT_MOVE_DOWN			'd'
#define OBJECT_MOVE_LEFT			'l'
#define OBJECT_MOVE_RIGHT			'r'
#define OBJECT_NOT_MOVING			'n'


#define getMapObjNum(x, y)			map.at(y).at(x)
#define getRandom(min, max)			(rand() % (max-max+1)) + min

#define isSameLocation(obj, x, y)	obj getXOnMap() == x && obj getYOnMap() == y

	enum MapObject {
		MAPOBJ_MAPEND = -1,
		MAPOBJ_EDGE,
		MAPOBJ_MOVABLE,
		MAPOBJ_HERO,
		MAPOBJ_PRINCESS,
		MAPOBJ_ROCK,
		MAPOBJ_ENEMY,
		MAPOBJ_KEY,
		MAPOBJ_LOCK
	};

	class HStage {
	public:
		HStage();
		HStage(CGameStateRun* mainState);
		~HStage();

		void RestartStage();

		void Initialize(vector<vector<int>> init_map);

		void LoadBitmap();

		void OnShow();
		void OnMove();

		void HeroWantToMove(char direction);

		void quickPass();

		void setXY(int nx, int ny);

		const int findObjectsX(int xInMap);
		const int findObjectsY(int yInMap);

		const int getX();
		const int getY();

		const vector<vector<int>>* getMap();

		HMapObject* getMapObject(int xOnMap, int yOnMap);

		HStage* getNextStage();

		HHero* getHero();
		HPrincess* getPrincess();
		vector<HRock>* getRocks();
		vector<HEnemy>* getEnemies();
		HKey* getKey();
		HLock* getLock();

	protected:
		virtual void basicSetup();

		// Load my background bitmap. This method must be overwrited by
		// inherit classes.
		virtual void loadMyBitmap();
		// Load other objects' bitmaps.
		void loadOtherBitmaps();

		// Update dynamic map.
		void updateDynamicMap();

		// The background image of the stage.
		CAnimation backgroundImage = CAnimation();

		// The location in frame.
		int x, y;

		// Determine that when any map object's setXYOnMap() called, these
		// values should added on their coordinate.
		// This will be needed by some stage which their maps' height and
		// width cannot be devided by 100.
		int xOffset, yOffset;

		// The width of every object. Every object in the map should be
		// square, and their actual location in frame should be calculated
		// by adding the multiply of objectWidth and their location in map
		// to the actual location of this stage in frame.
		int objectWidth = 100;

		// When the stage restarted, load this map.
		vector<vector<int>> STAGE_MAP;

		// The map of the stage. It's dynamic so object can directly move
		// on this variable.
		vector<vector<int>> map;

		// The actual map size.
		int map_width, map_height;

		// The maximum move steps.
		int MAX_MOVE_STEPS;
		// How many steps hero can move last.
		int steps_left;

		// Next stage. When stage clear, jump to this stage.
		HStage* nextStage;

		HStepsDisplay* stepsDisplay;

		HHero* hero = new HHero();
		HPrincess* princess = new HPrincess();
		vector<HRock>* rocks;
		vector<HEnemy>* enemies;
		HKey* key = new HKey();
		HLock* lock = new HLock();

		int whichPrincess;

		int rocksCount = 0;
		int enemiesCount = 0;

		bool hasLock = false;

		CGameStateRun* mainState;

	};

#endif
}