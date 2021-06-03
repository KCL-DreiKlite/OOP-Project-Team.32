#include "HMapObject.h"

namespace game_framework {

#ifndef _HPRINCESS_H_
#define _HPRINCESS_H_

#define PRINCESS_LUCIFER 1

	class HPrincess : public HMapObject {
	public:
		HPrincess();

		void Initialize(int onMapX, int onMapY, int xOffset = 0, int yOffset = 0, int objectWidth = 100) override;				// 設定擦子為初始值
		void LoadBitmap(int whichPrincess);
		void OnMove() override;
		void OnShow() override;

		int getWhichPrincess();
	protected:

		// Which princess should I load for bitmaps
		int whichPrincess = -1;

	};

#endif
}