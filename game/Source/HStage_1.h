
namespace game_framework {

	class HStage_1 : public HStage {
	public:

	protected:


		// The map of this stage.
		bool stg1_mapEdge[9][11] = { {0,0,0,0,0,0,0,0,0,0,0},
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