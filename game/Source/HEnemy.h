

namespace game_framework {
#define ENEMY_MOVE_UP		'u'
#define ENEMY_MOVE_DOWN		'd'
#define ENEMY_MOVE_LEFT		'l'
#define ENEMY_MOVE_RIGHT	'r'
#define ENEMY_NOT_MOVING	'n'


#ifndef _HENEMY_H_
#define _HENEMY_H_

	class HEnemy {
	public:
		HEnemy();
		int getX1();
		int getY1();
		int getX2();
		int getY2();
		void Initialize(int xOnMap, int yOnMap, int objectWidth);				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetMovingDirection(char direction);
		void SetXY(int nx, int ny);
		int getXOnMap();
		int getYOnMap();
		void SetIsAlive(bool alive);    //是否活著
	protected:
		const int animation_tickPerFrame = 2;
		CAnimation animation = CAnimation(animation_tickPerFrame);		// 擦子的動畫
		int x, y;					// 擦子左上角座標
		int onMapX, onMapY;		// The coordinate on mapEdge
		//bool isMovingDown;			// 是否正在往下移動
		//bool isMovingLeft;			// 是否正在往左移動
		//bool isMovingRight;			// 是否正在往右移動
		//bool isMovingUp;			// 是否正在往上移動

		const int stepPerTick = 50;
		const int maximumSteps = 100;

		bool isMoving;
		int stepCounter;
		char movingDirection;
		bool is_alive;				// 是否活著
	};

#endif
}