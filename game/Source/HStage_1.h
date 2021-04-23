
namespace game_framework {

	class HStage_1 : public HStage {
	public:
		HStage_1();
		~HStage_1();
	protected:


		// The map of this stage.
		const bool stg1_map[9][11] = { {0,0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,1,1,1,0,0,0,0},
									{0,0,0,0,1,1,1,0,0,0,0},
									{0,0,1,0,1,1,1,0,1,0,0},
									{0,1,1,1,1,1,1,1,1,1,0},
									{0,1,1,1,1,1,1,1,1,1,0},
									{0,0,1,1,1,1,1,1,1,0,0},
									{0,0,0,0,0,0,0,0,0,0,0} };

		// Inherit the father method.
		void loadMyBitmap() override;
	};
}