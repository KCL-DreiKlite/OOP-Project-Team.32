#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include <vector>
#include <stdlib.h>

#include "HHero.h"
#include "HPrincess.h"
#include "HRock.h"
#include "HEnemy.h"
#include "HKey.h"
#include "HLock.h"
#include "HStage.h"

#include "HStage_1.h"

//#include <vector>
//
//#include "HStage.h"

namespace game_framework {

	void HStage_1::loadMyBitmap() {
		backgroundImage.LoadBitmap(".\\Bitmaps\\Chapter 9-1.bmp");
	}
}