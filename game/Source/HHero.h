

namespace game_framework {
#define HERO_MOVE_UP 'u'
#define HERO_MOVE_DOWN 'd'
#define HERO_MOVE_LEFT 'l'
#define HERO_MOVE_RIGHT 'r'
#define HERO_NOT_MOVING 'n'

#define HERO_FACING_LEFT	'l'
#define HERO_FACING_RIGHT	'r'

	class HHero
	{
	public:
		HHero();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		void Initialize(int onMapX, int onMapY, int objectWidth);				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		//void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		//void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		//void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		//void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetMovingDirection(char direction);
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		void SetHeroDirectionBitmap(char face);
		void HeroAttacking();

		int getXOnMap();
		int getYOnMap();
	protected:
		const int animation_tickPerFrame = 2;
		CAnimation animation = CAnimation(animation_tickPerFrame);		// ���l���ʵe
		int x, y;					// ���l���W���y��
		int onMapX,onMapY;		// The coordinate on mapEdge
		//bool isMovingDown;			// �O�_���b���U����
		//bool isMovingLeft;			// �O�_���b��������
		//bool isMovingRight;			// �O�_���b���k����
		//bool isMovingUp;			// �O�_���b���W����

		const int stepPerTick = 50;
		const int maximumSteps = 100;

		bool isMoving;
		int stepCounter;
		char movingDirection;
		char faceDirection;

		//bool	mapEdge[9][11] = { {0,0,0,0,0,0,0,0,0,0,0},
		//							{0,0,0,0,0,0,0,0,0,0,0},
		//							{0,0,0,0,1,1,1,0,0,0,0},
		//							{0,0,0,0,1,1,1,0,0,0,0},
		//							{0,0,1,0,1,1,1,0,1,0,0},
		//							{0,1,1,1,1,1,1,1,1,1,0},
		//							{0,1,1,1,1,1,1,1,1,1,0},
		//							{0,0,1,1,1,1,1,1,1,0,0},
		//							{0,0,0,0,0,0,0,0,0,0,0} };
	};
}
