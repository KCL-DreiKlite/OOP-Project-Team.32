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
		void Initialize(int onMapX, int onMapY, int xOffset = 0, int yOffset = 0, int objectWidth = 100) override;				// �]�w���l����l��
		void LoadBitmap() override;				// ���J�ϧ�
		void OnMove() override;					// �������l
		void OnShow() override;					// �N���l�ϧζK��e��

		void SetMovingDirection(char direction);
		void SetHeroDirectionBitmap(char face);
		void HeroAttacking();
		void SetHeroMoved();
		void SetHeroStopped();
		bool heroIsMoved();  //hero�O�_����

	protected:
		const int stepPerTick = 50;
		const int maximumSteps = 100;

		bool isMoving;
		int stepCounter;
		char movingDirection;
		char faceDirection;
		bool heroMoved;  //hero���ӨB��

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
