#include "HMapObject.h"

namespace game_framework {

#ifndef _HKEY_H_
#define _HKEY_H_

	class HKey : public HMapObject {
	public:
		HKey();

		void Initialize(int xOnMap, int yOnMap, int objectWidth) override;				// 設定擦子為初始值
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
