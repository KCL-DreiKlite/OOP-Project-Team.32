

namespace game_framework {
#define HERO_MOVE_UP 'u'
#define HERO_MOVE_DOWN 'd'
#define HERO_MOVE_LEFT 'l'
#define HERO_MOVE_RIGHT 'r'
#define HERO_NOT_MOVING 'n'

#define HERO_FACING_LEFT	'l'
#define HERO_FACING_RIGHT	'r'

	class HHero
	{
	public:
		HHero();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void Initialize(int onMapX, int onMapY, int objectWidth);				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		//void SetMovingDown(bool flag);	// 設定是否正在往下移動
		//void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		//void SetMovingRight(bool flag); // 設定是否正在往右移動
		//void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetMovingDirection(char direction);
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		void SetHeroDirectionBitmap(char face);
		void HeroAttacking();

		int getXOnMap();
		int getYOnMap();
	protected:
		const int animation_tickPerFrame = 2;
		CAnimation animation = CAnimation(animation_tickPerFrame);		// 擦子的動畫
		int x, y;					// 擦子左上角座標
		int onMapX,onMapY;		// The coordinate on mapEdge
		//bool isMovingDown;			// 是否正在往下移動
		//bool isMovingLeft;			// 是否正在往左移動
		//bool isMovingRight;			// 是否正在往右移動
		//bool isMovingUp;			// 是否正在往上移動

		const int stepPerTick = 50;
		const int maximumSteps = 100;

		bool isMoving;
		int stepCounter;
		char movingDirection;
		char faceDirection;

		//bool	mapEdge[9][11] = { {0,0,0,0,0,0,0,0,0,0,0},
		//							{0,0,0,0,0,0,0,0,0,0,0},
		//							{0,0,0,0,1,1,1,0,0,0,0},
		//							{0,0,0,0,1,1,1,0,0,0,0},
		//							{0,0,1,0,1,1,1,0,1,0,0},
		//							{0,1,1,1,1,1,1,1,1,1,0},
		//							{0,1,1,1,1,1,1,1,1,1,0},
		//							{0,0,1,1,1,1,1,1,1,0,0},
		//							{0,0,0,0,0,0,0,0,0,0,0} };
	};
}
