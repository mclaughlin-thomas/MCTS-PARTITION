#include "connectboard.h"


Connect4Board::Connect4Board() {

	setupBoard();
}

Connect4Board::~Connect4Board() {
	//std::cout << "desructor\n";
}

Connect4Board::Connect4Board(int turn) {

	this->turn = turn;
	setupBoard();
}
void Connect4Board::selectFirst(int first) {
	if (first == 1) {
		turn = 1;
	}
	else {
		turn = -1;
	}
}

Connect4Board::Connect4Board(const Connect4Board& nBoard) {

	setupBoard();

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			board[i][j] = nBoard.board[i][j];
		}
	}

	turn = nBoard.turn;

}

vector<int> Connect4Board::legal_moves() {
	extern int firstCol;


	if (firstCol == -1) {
		//std::cout << "not yet legal" << endl;
		vector<int> temp;

		for (int rows = 0; rows < COLS; rows++) {
			if (board[0][rows] == 0) {
				temp.push_back(rows);
			}
		}
		return temp;
	}
	//std::cout << "Beneath not legal" << endl;

	//MAKE FCN HERE FOR IF WE GO FIRST TO BREAK IN FRESH BOARD AND BOARD SIZE IS LARGE, MAKE RANGE BE LIKE FROM MIDDLE TO RIGHTMOST SIDE

	if (ROWS < 5 && COLS < 5) {
		vector<int> temp;

		for (int rows = 0; rows < COLS; rows++) {
			if (board[0][rows] == 0) {
				temp.push_back(rows);
			}
		}
		return temp;
	}
	
	else {
		//std::cout << "legal RANGE :: " << firstCol << endl;
		//std::cout << "LEGAL RANGE" << endl;
		//std::cout << "Parition range: " << firstCol - 5 << " to " << firstCol + 5 << endl;
		vector<int> temp;

		int startCol = firstCol - 5; // Ensure startCol is not less than 0.
		int endCol = firstCol + 5; // Ensure endCol does not exceed the board size.
		if (startCol < 0) {
			startCol = 0;
		}
		int leftover = COLS - 1 - endCol;
		if (endCol > COLS - 1) {
			endCol = COLS - 1;
		}

		//std::cout << "start col: " << startCol << endl;
		//std::cout << "end col: " << endCol << endl;

		for (int col = startCol; col <= endCol; col++) {
			if (board[0][col] == 0) {
				temp.push_back(col);
			}
		}
		return temp;
	}

}


int Connect4Board::getFirstCol() {
	extern int firstCol;
	return firstCol;
}
void Connect4Board::setFirstCol(int col) {
	extern int firstCol;
	firstCol = col;
}




void Connect4Board::print() {

	if (BOARD_PRINTING == -1) {
		//do nothing, no print
	}
	else if (BOARD_PRINTING == 1) {
		//cout << " 0  1  2  3  4  5  6" << endl;
		//cout << "____________________" << endl;

		// ^^ old way of hardcoding, this new way should allow it to be dynamic:
		int colCount = 0;

		for (int i = 0; i < COLS; i++) {
			std::cout << " " << colCount << " ";
			colCount++;
		}
		std::cout << endl;
		for (int i = 0; i < COLS; i++) {
			std::cout << "___";
		}
		std::cout << endl;

		// this should print a similar output, with any size

		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {


				if (board[i][j] == 1) {
					std::cout << " " << "X" << " ";
				}
				if (board[i][j] == -1) {
					std::cout << " " << "O" << " ";
				}
				if (board[i][j] == 0) {
					std::cout << " " << "." << " ";
				}
			}

			std::cout << endl;
		}
		std::cout << endl;
	}
	else if (BOARD_PRINTING == 0) {
		//std::cout << this->getFirstCol() << "\n";
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if (board[i][j] == 1) {
					std::cout << "X in column " << j << " row " << i << endl;
				}
				if (board[i][j] == -1) {
					std::cout << "O in column " << j << " row " << i << endl;
				}
			}
		}

	}
	else {
		std::cout << "invalid board printing option (please set to 1 to enable or 0 to disable)" << endl;
	}


}

void Connect4Board::make_move(int col) {

	if (allowed(col)) {
		for (int i = ROWS - 1; i >= 0; i--) {
			if (board[i][col] == 0) {
				board[i][col] = turn;
				turn = -turn; // swtich turns
				return;
			}
		}
	}
	std::cout << "move not allowed." << endl;
	std::cout << "no changes made" << endl;
	return;

}

void Connect4Board::switchPlayer() {
	turn = -turn;
}

bool Connect4Board::allowed(int col) {
	if (col < 0 || col > COLS - 1) {
		return false;
	}
	else {
		if (board[0][col] == 0) {
			return true;
		}
	}
	return false;
}

int Connect4Board::getTurn() {
	return turn;
}

bool Connect4Board::getFirst() {
	return _firstTimeHuh;
}

void Connect4Board::setFirst(bool first) {
	_firstTimeHuh = first;
}

int Connect4Board::result() {
	int score = 2;

	// 1 AI win, -1 opps win, 2 cont, 0 tie
	// hor
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS - 3; j++) {
			score = board[i][j] + board[i][j + 1] + board[i][j + 2] + board[i][j + 3];
			if (score == 4) {
				return 1;
			}
			else if (score == -4) {
				return -1;
			}
			else {
				score = 2;
			}
		}

	}



	//vert
	for (int i = 0; i < ROWS - 3; i++) {
		for (int j = 0; j < COLS; j++) {
			score = board[i][j] + board[i + 1][j] + board[i + 2][j] + board[i + 3][j];
			if (score == 4) {
				return 1;
			}
			else if (score == -4) {
				return -1;
			}
			else {
				score = 2;
			}
		}

	}

	//diag
	for (int i = 0; i < ROWS - 3; i++) {
		for (int j = 0; j < COLS - 3; j++) {
			score = board[i][j] + board[i + 1][j + 1] + board[i + 2][j + 2] + board[i + 3][j + 3];
			if (score == 4) {
				return 1;
			}
			else if (score == -4) {
				return -1;
			}
			else {
				score = 2;
			}
		}

	}

	//diag
	for (int i = 3; i < ROWS; i++) {
		for (int j = 0; j < COLS - 3; j++) {
			score = board[i][j] + board[i - 1][j + 1] + board[i - 2][j + 2] + board[i - 3][j + 3];
			if (score == 4) {
				return 1;
			}
			else if (score == -4) {
				return -1;
			}
			else {
				score = 2;
			}
		}

	}


	if (is_fully_expanded()) {
		return 0;
	}

	return score;
}

bool Connect4Board::is_fully_expanded() {
	//may need to tweak some more,aiden check this out more n test please
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

bool Connect4Board::terminalOutcome() {
	if (result() == 1 || result() == -1 || result() == 0) return true;
	else return false;
}

void Connect4Board::restart() {
	setupBoard();
	turn = 1;
}

void Connect4Board::invert() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			board[i][j] = -1 * board[i][j];
		}
	}
	turn = -1 * turn;
}

void Connect4Board::setupBoard() {

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			board[i][j] = 0;
		}
	}
}
