
namespace game_framework {

	class HKey {
	public:
		HKey();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize(int onMapX, int onMapY, int objectWidth);
		void LoadBitmap();				
		void OnMove();					
		void OnShow();					
		void SetXY(int nx, int ny);
		int getXOnMap();
		int getYOnMap();
		void SetIsAlive(bool alive);    //是否活著
		bool HKey::IsAlive();
	protected:
		const int animation_tickPerFrame = 2;
		CAnimation animation = CAnimation(animation_tickPerFrame);		
		int x, y;					
		int onMapX, onMapY;		
		bool is_alive;
	};

}
