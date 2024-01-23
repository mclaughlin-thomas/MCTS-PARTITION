#pragma once
#include "globals.h"
#include "connectboard.h"
#include "monte.h"

class AI {
public:
	AI(double c_param); 
	int pick_col(Connect4Board* board);

private:
	MonteCarloTreeSearch* monte;
	bool firstTimeHuh = true;

};
