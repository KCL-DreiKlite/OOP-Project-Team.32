
namespace game_framework {


#ifndef _HMAPOBJECT_H_
#define _HMAPOBJECT_H_

	class HMapObject {
	public:
		HMapObject();

		virtual void Initialize(int onMapX, int onMapY, int objectWidth);
		virtual void LoadBitmap();				// 載入圖形

		virtual void OnMove();					// 移動擦子
		virtual void OnShow();					// 將擦子圖形貼到畫面

		void SetMovingDirection(char direction);
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		void SetXYOnMap(int nx, int ny);

		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標

		int getXOnMap();
		int getYOnMap();
	protected:
		const int animation_tickPerFrame = 2;
		CAnimation animation = CAnimation(animation_tickPerFrame);
		int x, y;
		int onMapX, onMapY;		// The coordinate on mapEdge
		int objectWidth;		// This object's bitmap width.

	};
#endif // !_HMAPOBJECT_H_

}