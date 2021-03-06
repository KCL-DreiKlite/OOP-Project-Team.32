#include "HMapObject.h"

namespace game_framework {

#ifndef _HROCK_H_
#define _HROCK_H_

#define ROCK_MOVE_UP	'u'
#define ROCK_MOVE_DOWN	'd'
#define ROCK_MOVE_LEFT	'l'
#define ROCK_MOVE_RIGHT	'r'
#define ROCK_NOT_MOVING	'n'

#define ROCK_BMP_0		0
#define ROCK_BMP_1		1
#define ROCK_BMP_2		2

	class HRock : public HMapObject {
	public:
		HRock();

		void Initialize(int onMapX, int onMapY, int xOffset = 0, int yOffset = 0, int objectWidth = 100) override;				// 設定擦子為初始值
		void LoadBitmap(int whichRockImage);
		void OnMove() override;
		void OnShow() override;

		void SetMovingDirection(char direction);

		void SetIsAlive(bool alive);    //是否活著

		bool IsAlive();
	protected:
		int whichRockImage;

		const int stepPerTick = 50;
		const int maximumSteps = 100;

		bool isMoving;
		int stepCounter;
		char movingDirection;
		bool is_alive;				// 是否活著
	};

#endif
}