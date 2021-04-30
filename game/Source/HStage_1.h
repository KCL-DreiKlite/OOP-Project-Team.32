
namespace game_framework {

	class HStage_1 : public HStage {
	public:
		HStage_1();
		~HStage_1();

		void Initialize();
	protected:


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

		
	};
}