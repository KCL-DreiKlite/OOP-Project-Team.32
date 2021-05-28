#include "HMapObject.h"

namespace game_framework {
#define PRINCESS_LUCIFER 1

#ifndef _HPRINCESS_H_
#define _HPRINCESS_H_

	class HPrincess : public HMapObject {
	public:
		HPrincess();

		void Initialize(int xOnMap, int yOnMap, int objectWidth) override;				// 設定擦子為初始值
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