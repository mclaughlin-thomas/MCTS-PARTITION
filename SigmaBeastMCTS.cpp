#include "SigmaBeastMCTS.h"

AI::AI(double c_param) {
	monte = new MonteCarloTreeSearch(c_param);
}

int AI::pick_col(Connect4Board* board) {
	
	int best = monte->search(*board);
	std::cout<<std::endl<<"dropping in col "<<best<<std::endl;
	return best;
}
