#include "HMapObject.h"

namespace game_framework {
#ifndef _HLOCK_H_
#define _HLOCK_H_

	class HLock : public HMapObject {
	public:
		HLock();

		void Initialize(int onMapX, int onMapY, int xOffset = 0, int yOffset = 0, int objectWidth = 100) override;				// �]�w���l����l��
		void LoadBitmap() override;
		void OnMove() override;
		void OnShow() override;

		void SetIsAlive(bool alive);    //�O�_����

		bool IsAlive();
	protected:

		bool is_alive;
	};

#endif
}
