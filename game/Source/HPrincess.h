
namespace game_framework {
#define PRINCESS_LUCIFER 1


	class HPrincess {
	public:
		HPrincess();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize(int whichPrincess);
		void LoadBitmap();				// 載入圖形
		void OnMove(bool mapEdge[][11]);					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetXY(int nx, int ny);
		int getXOnMap();
		int getYOnMap();
	protected:
		const int animation_tickPerFrame = 2;
		CAnimation animation = CAnimation(animation_tickPerFrame);		// 擦子的動畫
		int x, y;					// 擦子左上角座標
		int onMapX, onMapY;		// The coordinate on mapEdge
		int whichPrincess;

	};

}