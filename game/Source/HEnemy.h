

namespace game_framework {
#define ENEMY_MOVE_UP		'u'
#define ENEMY_MOVE_DOWN		'd'
#define ENEMY_MOVE_LEFT		'l'
#define ENEMY_MOVE_RIGHT	'r'
#define ENEMY_NOT_MOVING	'n'


#ifndef _HENEMY_H_
#define _HENEMY_H_

	class HEnemy {
	public:
		HEnemy();
		int getX1();
		int getY1();
		int getX2();
		int getY2();
		void Initialize(int xOnMap, int yOnMap, int objectWidth);				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void SetMovingDirection(char direction);
		void SetXY(int nx, int ny);
		int getXOnMap();
		int getYOnMap();
		void SetIsAlive(bool alive);    //�O�_����
	protected:
		const int animation_tickPerFrame = 2;
		CAnimation animation = CAnimation(animation_tickPerFrame);		// ���l���ʵe
		int x, y;					// ���l���W���y��
		int onMapX, onMapY;		// The coordinate on mapEdge
		//bool isMovingDown;			// �O�_���b���U����
		//bool isMovingLeft;			// �O�_���b��������
		//bool isMovingRight;			// �O�_���b���k����
		//bool isMovingUp;			// �O�_���b���W����

		const int stepPerTick = 50;
		const int maximumSteps = 100;

		bool isMoving;
		int stepCounter;
		char movingDirection;
		bool is_alive;				// �O�_����
	};

#endif
}