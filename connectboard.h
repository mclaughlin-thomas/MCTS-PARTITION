#pragma once
#include "globals.h"


class Connect4Board {
public:
	Connect4Board();
	~Connect4Board();
	Connect4Board(int turn);
	Connect4Board(const Connect4Board& nBoard);
	vector<int> legal_moves();
	void print();
	void make_move(int col);
	bool allowed(int col);
	void selectFirst(int first);
	void switchPlayer();
	int getTurn();
	bool getFirst();
	void invert();
	void setFirst(bool first);
	void restart();
	bool terminalOutcome();
	bool is_fully_expanded();
	int result();
private:
	int turn = 1;
	int x = 1; // p1
	int o = -1; // p2
	int board[ROWS][COLS];
	void setupBoard(); // matix of 0's
	bool _firstTimeHuh = true;

};
