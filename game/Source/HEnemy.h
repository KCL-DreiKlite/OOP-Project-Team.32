#include "HMapObject.h"

namespace game_framework {

#ifndef _HENEMY_H_
#define _HENEMY_H_

#define ENEMY_MOVE_UP		'u'
#define ENEMY_MOVE_DOWN		'd'
#define ENEMY_MOVE_LEFT		'l'
#define ENEMY_MOVE_RIGHT	'r'
#define ENEMY_NOT_MOVING	'n'


	class HEnemy : public HMapObject {
	public:
		HEnemy();

		void Initialize(int onMapX, int onMapY, int xOffset = 0, int yOffset = 0, int objectWidth = 100) override;				// �]�w���l����l��
		void LoadBitmap() override;
		void OnMove() override;
		void OnShow() override;

		void SetMovingDirection(char direction);

		void SetIsAlive(bool alive);    //�O�_����

		bool IsAlive();
	protected:

		const int stepPerTick = 50;
		const int maximumSteps = 100;

		bool isMoving;
		int stepCounter;
		char movingDirection;
		bool is_alive;				// �O�_����
	};

#endif
}