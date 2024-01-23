#pragma once
#include "user.h"
#include "globals.h"
#include "connectboard.h"
#include "SigmaBeastMCTS.h"
//test

class Arena {
public:
	Arena();
	~Arena();
	Arena(AI& agentAI, AI& agentUser, Connect4Board& board);
	int execute();
	Connect4Board getBoard();
	AI getAI();
	User getUser();
	void setBoard(Connect4Board& board);
	void setAI(AI& agentAI);
	//void setUser(User& agentUser);
private:
	AI* agentAI;
	AI* agentUser; //aid, why not keep inheritance?
	Connect4Board* board;
};

