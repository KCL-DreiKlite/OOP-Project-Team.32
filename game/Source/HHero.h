#include "HMapObject.h"

namespace game_framework {
#define HERO_MOVE_UP 'u'
#define HERO_MOVE_DOWN 'd'
#define HERO_MOVE_LEFT 'l'
#define HERO_MOVE_RIGHT 'r'
#define HERO_NOT_MOVING 'n'

#define HERO_FACING_LEFT	'l'
#define HERO_FACING_RIGHT	'r'

#ifndef _HHERO_H_
#define _HHERO_H_

	class HHero : public HMapObject
	{
	public:
		HHero();
		void Initialize(int onMapX, int onMapY, int xOffset = 0, int yOffset = 0, int objectWidth = 100) override;				// 設定擦子為初始值
		void LoadBitmap() override;				// 載入圖形
		void OnMove() override;					// 移動擦子
		void OnShow() override;					// 將擦子圖形貼到畫面

		void SetMovingDirection(char direction);
		void SetHeroDirectionBitmap(char face);
		void HeroAttacking();
		void SetHeroMoved();
		void SetHeroStopped();
		bool heroIsMoved();  //hero是否移動

	protected:
		const int stepPerTick = 50;
		const int maximumSteps = 100;

		bool isMoving;
		int stepCounter;
		char movingDirection;
		char faceDirection;
		bool heroMoved;  //hero消耗步數

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
#endif // !_HHERO_H_

}
