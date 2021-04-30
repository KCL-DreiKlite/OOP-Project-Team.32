
namespace game_framework {
#define PRINCESS_LUCIFER 1


	class HPrincess {
	public:
		HPrincess();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize(int onMapX, int onMapY, int objectWidth);
		void LoadBitmap(int whichPrincess);				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetXY(int nx, int ny);
		int getXOnMap();
		int getYOnMap();
		int getWhichPrincess();
	protected:
		const int animation_tickPerFrame = 2;
		CAnimation animation = CAnimation(animation_tickPerFrame);		// 擦子的動畫
		int x, y;					// 擦子左上角座標

		// The coordinate on mapEdge
		int onMapX, onMapY;

		// Which princess should I load for bitmaps
		int whichPrincess = -1;

	};

}