
namespace game_framework {


#ifndef _HMAPOBJECT_H_
#define _HMAPOBJECT_H_

	class HMapObject {
	public:
		HMapObject();

		virtual void Initialize(int onMapX, int onMapY, int xOffset = 0, int yOffset = 0, int objectWidth = 100);
		virtual void LoadBitmap();				// ���J�ϧ�

		virtual void OnMove();					// �������l
		virtual void OnShow();					// �N���l�ϧζK��e��

		virtual void setXY(int nx, int ny);		// �]�w���l���W���y��
		virtual void setXYOnMap(int nx, int ny);
		virtual void setXOffset(int xOffset);
		virtual void setYOffset(int yOffset);
		virtual void setXYOffset(int xOffset, int yOffset);

		int  getX1();					// ���l���W�� x �y��
		int  getY1();					// ���l���W�� y �y��
		int  getX2();					// ���l�k�U�� x �y��
		int  getY2();					// ���l�k�U�� y �y��

		int getXOnMap();
		int getYOnMap();

		int getXOffset();
		int getYOffset();
	protected:
		const int animation_tickPerFrame = 2;
		CAnimation animation = CAnimation(animation_tickPerFrame);

		int x, y;
		int xOffset, yOffset;
		int onMapX, onMapY;		// The coordinate on mapEdge
		int objectWidth;		// This object's bitmap width.

	};
#endif // !_HMAPOBJECT_H_

}