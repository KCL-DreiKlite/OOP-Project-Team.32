
namespace game_framework {

#ifndef _HStage_2_
#define _HStage_2_

#define IMAGE_STAGE_2		".\\Bitmaps\\STAGE_MAP\\stg2.bmp"

	class HStage_2 : public HStage {
	public:
		HStage_2();
		HStage_2(CGameStateRun* mainState);

		~HStage_2();

		void Initialize();
	protected:
		void basicSetup() override;

		// The map of this stage.
		const int stg2_map[8][9] = { {0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,1,2,0,0},
									{0,0,1,1,5,1,1,0,0},
									{0,0,1,5,1,5,0,0,0},
									{0,1,1,0,0,0,0,0,0},
									{0,1,4,1,1,4,1,0,0},
									{0,1,4,1,4,1,1,3,0},
									{0,0,0,0,0,0,0,0,0} };

		// Inherit the father method.
		void loadMyBitmap() override;

		// The maximum steps of stage 2.
		const int STG2_MAX_MOVE_STEP = 24;
	};

#endif
}