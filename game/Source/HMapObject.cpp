#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "HMapObject.h"

namespace game_framework {
	HMapObject::HMapObject() {

	}

	void HMapObject::Initialize(int onMapX, int onMapY, int objectWidth) {
		this->onMapX = onMapX; this->onMapY = onMapY;
		this->x = onMapX * objectWidth; this->y = onMapY * objectWidth;
		this->objectWidth = objectWidth;
	}

	void HMapObject::LoadBitmap() {}
	void HMapObject::OnMove() {}
	void HMapObject::OnShow() {}


	void HMapObject::setXY(int nx, int ny) {
		this->x = nx;
		this->y = ny;
	}

	void HMapObject::setXYOnMap(int nx, int ny) {
		this->onMapX = nx;
		this->onMapY = ny;
	}
	
	int HMapObject::getX1() { return x; }
	int HMapObject::getY1() { return y; }
	int HMapObject::getX2() { return x + animation.Width(); }
	int HMapObject::getY2() { return y + animation.Height(); }

	int HMapObject::getXOnMap() { return onMapX; }
	int HMapObject::getYOnMap() { return onMapY; }

}