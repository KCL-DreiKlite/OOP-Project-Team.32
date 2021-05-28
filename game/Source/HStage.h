
namespace game_framework {
#define MAX_AVAILABLE_MAP_WIDTH		20
#define MAX_AVAILABLE_MAP_HEIGHT	20

#define MAPOBJ_MAPEND		-1
#define MAPOBJ_EDGE			0
#define MAPOBJ_MOVABLE		1
#define MAPOBJ_HERO			2
#define MAPOBJ_PRINCESS		3
#define MAPOBJ_ROCK			4
#define MAPOBJ_ENEMY		5
#define MAPOBJ_KEY			6
#define MAPOBJ_LOCK			7

#define IMAGE_STAGE_1		".\\Bitmaps\\Chapter 9-1.bmp"

#define objectInMap(x, y)	map.at(y).at(x)
#define getRandom(min, max)	 (rand() % (max-max+1)) + min

#ifndef _HSTAGE_H_
#define _HSTAGE_H_

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

		void setXY(int nx, int ny);

		const int findObjectsX(int xInMap);
		const int findObjectsY(int yInMap);

		const int getX();
		const int getY();

		const vector<vector<int>>* getMap();

		//const int getWidth();
		//const int getHeight();

		HHero* getHero();
		HPrincess* getPrincess();
		vector<HRock>* getRocks();
		vector<HEnemy>* getEnemies();
		HKey* getKey();
		HLock* getLock();

	protected:
		// Load my background bitmap. This method must be overwrited by
		// inherit classes.
		virtual void loadMyBitmap();
		// Load other objects' bitmaps.
		void loadOtherBitmaps();

		// The background image of the stage.
		CAnimation backgroundImage = CAnimation();

		// The location in frame.
		int x, y;

		// The width of every object. Every object in the map should be
		// square, and their actual location in frame should be calculated
		// by adding the multiply of objectWidth and their location in map
		// to the actual location of this stage in frame.
		int objectWidth = 100;

		// The map of the stage. It's dynamic so object can directly move
		// on this variable.
		vector<vector<int>> map;

		// The actual map size.
		int map_width, map_height;

		// The maximum move steps.
		int MAX_MOVE_STEPS;
		// How many steps hero can move last.
		int steps_left;


		HHero* hero = new HHero();
		HPrincess* princess = new HPrincess();
		vector<HRock>* rocks;
		vector<HEnemy>* enemies;
		HKey* key = new HKey();
		HLock* lock = new HLock();

		int whichPrincess;

		int rocksCount = 0;
		int enemiesCount = 0;

		bool hasLock;

		CGameStateRun* mainState;
	};

#endif
}