#include "user.h"

User::User() {
 //we dont set anything
}

int User::pick_col(Connect4Board* board) {

	int col = 0;
	cout << "Enter col " << endl;
	cin >> col;

	return col;
}
