
namespace game_framework {

#ifndef _HSTAGE_1_
#define _HSTAGE_1_

#define IMAGE_STAGE_1		".\\Bitmaps\\STAGE_MAP\\stg1.bmp"

	class HStage_1 : public HStage {
	public:
		HStage_1();
		HStage_1(CGameStateRun* mainState);

		~HStage_1();

		void Initialize();
	protected:
		void basicSetup() override;

		// The map of this stage.
		const int stg1_map[9][11] = { {0,0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,1,3,1,0,0,0,0},
									{0,0,0,0,4,7,4,0,0,0,0},
									{0,0,4,0,4,1,1,0,1,0,0},
									{0,4,1,1,4,4,4,1,1,6,0},
									{0,1,4,4,4,1,1,4,4,1,0},
									{0,0,2,1,4,1,1,4,1,0,0},
									{0,0,0,0,0,0,0,0,0,0,0} };

		// Inherit the father method.
		void loadMyBitmap() override;

		// The maximum steps of stage 1.
		const int STG1_MAX_MOVE_STEP = 33;
	};

#endif
}