
namespace game_framework {

#ifndef _HStage_3_
#define _HStage_3_

#define IMAGE_STAGE_3		".\\Bitmaps\\STAGE_MAP\\stg3.bmp"

	class HStage_3 : public HStage {
	public:
		HStage_3();
		HStage_3(CGameStateRun* mainState);

		~HStage_3();

		void Initialize();
	protected:
		void basicSetup() override;

		// The map of this stage.
		const int stg3_map[10][9] = { {0,0,0,0,0,0,0,0,0},
									  {0,0,1,2,1,0,0,0,0},
									  {0,0,4,4,4,0,0,0,0},
									  {0,4,1,1,6,0,0,0,0},
									  {0,0,1,1,1,1,0,0,0},
									  {0,0,5,0,4,4,1,1,0},
									  {0,0,1,1,4,1,5,0,0},
									  {0,0,0,0,0,7,4,1,0},
									  {0,0,0,0,0,1,3,0,0},
									  {0,0,0,0,0,0,0,0,0} };

		// Inherit the father method.
		void loadMyBitmap() override;

		// The maximum steps of stage 3.
		const int STG3_MAX_MOVE_STEP = 28;
	};

#endif
}