

namespace game_framework {
#define HERO_MOVE_UP 'u'
#define HERO_MOVE_DOWN 'd'
#define HERO_MOVE_LEFT 'l'
#define HERO_MOVE_RIGHT 'r'
#define HERO_NOT_MOVING 'n'

	class HHero
	{
	public:
		HHero();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		//void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		//void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		//void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		//void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetMovingDirection(char direction);
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
	protected:
		const int animation_tickPerFrame = 2;
		CAnimation animation = CAnimation(animation_tickPerFrame);		// ���l���ʵe
		int x, y;					// ���l���W���y��
		//bool isMovingDown;			// �O�_���b���U����
		//bool isMovingLeft;			// �O�_���b��������
		//bool isMovingRight;			// �O�_���b���k����
		//bool isMovingUp;			// �O�_���b���W����

		const int stepPerTick = 50;
		const int maximumSteps = 100;

		bool isMoving;
		int stepCounter;
		char movingDirection;

	};
}
