#include "HMapObject.h"

namespace game_framework {
#ifndef _HLOCK_H_
#define _HLOCK_H_

	class HLock : public HMapObject {
	public:
		HLock();

		void Initialize(int onMapX, int onMapY, int xOffset = 0, int yOffset = 0, int objectWidth = 100) override;				// 設定擦子為初始值
		void LoadBitmap() override;
		void OnMove() override;
		void OnShow() override;

		void SetIsAlive(bool alive);    //是否活著

		bool IsAlive();
	protected:

		bool is_alive;
	};

#endif
}
