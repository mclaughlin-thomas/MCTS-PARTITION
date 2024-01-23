#include "arena.h"


Arena::Arena() {
	this->agentAI = NULL;
	this->agentUser = NULL;
	this->board = NULL;
}

Arena::~Arena() {
	//std::cout << "desructor\n";
}

Arena::Arena(AI& agentAI, AI& agentUser, Connect4Board& board) {
	this->agentAI = &agentAI;
	this->agentUser = &agentUser;
	this->board = &board;
}

Connect4Board Arena::getBoard() {
	return *board;
}

AI Arena::getAI() {
	return *agentAI;
}

//User Arena::getUser() {
//	return *agentUser;
//}

void  Arena::setBoard(Connect4Board& board) {
	this->board = &board;
}

void  Arena::setAI(AI& agentAI) {
	this->agentAI = &agentAI;
}

//void  Arena::setUser(User& agentUser) {
//	this->agentUser = &agentUser;
//}

int Arena::execute() {

	while (board->result() == 2) {

		if (board->getTurn() == 1) {

			int a1 = agentAI->pick_col(board);
			while (!board->allowed(a1)) {
				a1 = agentAI->pick_col(board);
			}
			board->make_move(a1);
			board->print();
		}
		else if (board->getTurn() == -1) {

			int a2 = agentUser->pick_col(board);
			while (!board->allowed(a2)) {
				a2 = agentUser->pick_col(board);
			}
			board->make_move(a2);
			board->print();

		}
	}

	if (board->result() == 1 || board->result() == -1 || board->result() == 0) {
		return board->result();
	}
	else {
		std::cout << "Error in the Arena!" << std::endl;
		return 0;
	}
}

