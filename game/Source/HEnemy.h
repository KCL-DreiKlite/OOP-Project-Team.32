#include "HMapObject.h"

namespace game_framework {
#define ENEMY_MOVE_UP		'u'
#define ENEMY_MOVE_DOWN		'd'
#define ENEMY_MOVE_LEFT		'l'
#define ENEMY_MOVE_RIGHT	'r'
#define ENEMY_NOT_MOVING	'n'


#ifndef _HENEMY_H_
#define _HENEMY_H_

	class HEnemy : public HMapObject {
	public:
		HEnemy();

		void Initialize(int xOnMap, int yOnMap, int objectWidth) override;				// 設定擦子為初始值
		void LoadBitmap() override;
		void OnMove() override;
		void OnShow() override;

		void SetMovingDirection(char direction);

		void SetIsAlive(bool alive);    //是否活著
	protected:

		const int stepPerTick = 50;
		const int maximumSteps = 100;

		bool isMoving;
		int stepCounter;
		char movingDirection;
		bool is_alive;				// 是否活著
	};

#endif
}