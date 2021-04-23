
namespace game_framework {
#define ROCK_MOVE_UP	'u'
#define ROCK_MOVE_DOWN	'd'
#define ROCK_MOVE_LEFT	'l'
#define ROCK_MOVE_RIGHT	'r'
#define ROCK_NOT_MOVING	'n'

#define ROCK_BMP_0		'0'
#define ROCK_BMP_1		'1'
#define ROCK_BMP_2		'2'


	class HRock {
	public:
		HRock();
		int getX1();
		int getY1();
		int getX2();
		int getY2();
		void Initialize(int x, int y, int xOnMap, int yOnMap);				// 設定擦子為初始值
		void LoadBitmap(int whichRock);				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetMovingDirection(char direction);
		void SetXY(int nx, int ny);
		int getXOnMap();
		int getYOnMap();
	protected:
		int whichRockImage;

		CAnimation animation = CAnimation(1);
		int x, y;
		int onMapX, onMapY;

		const int stepPerTick = 50;
		const int maximumSteps = 100;

		bool isMoving;
		int stepCounter;
		char movingDirection;

	};
}