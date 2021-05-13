
namespace game_framework {
#ifndef _HLOCK_H_
#define _HLOCK_H_

	class HLock {
	public:
		HLock();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize(int onMapX, int onMapY, int objectWidth);
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetXY(int nx, int ny);
		void setXYOnMap(int nx, int ny);
		int getXOnMap();
		int getYOnMap();
		void SetIsAlive(bool alive);    //¬O§_¬¡µÛ
	protected:
		const int animation_tickPerFrame = 2;
		CAnimation animation = CAnimation(animation_tickPerFrame);
		int x, y;
		int onMapX, onMapY;
		bool is_alive;
	};

#endif
}
