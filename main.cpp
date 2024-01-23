#include "SigmaBeastMCTS.h"
#include "connectboard.h"
#include "user.h"
#include "globals.h"
#include "arena.h"
#include "monte.h"



std::chrono::time_point<std::chrono::seconds> maxNum;


int main(void) {

	srand(time(NULL));

	Connect4Board connect4Board;
	User userAgent;

	double c = sqrt(2);


	AI agent(c);
	AI agent2(c);
	int turnInput;

	//std::cout << "Select who goes first, you (The chump 0), or us (The sigma beasts 1).";
	//std::cin >> turnInput;
	turnInput = 1;
	connect4Board.selectFirst(turnInput);


	Arena arena(agent, agent2, connect4Board);


	int gameResult;
	gameResult = arena.execute();
	if (gameResult == 1) {
		std::cout << "AI wins!" << std::endl;
		//using namespace std::chrono_literals;
		//std::cout << "TIME FOR ENTIRE INTERATIONS: " << maxNum << std::endl;
		//std::this_thread::sleep_for(100s);
	}
	else if (gameResult == -1) {
		std::cout << "Opponent wins!" << std::endl;
		//std::cout << "TIME FOR ENTIRE INTERATIONS: " << maxNum << std::endl;
		using namespace std::chrono_literals;
		//std::this_thread::sleep_for(100s);
	}
	else {
		std::cout << "Tie! You lucked out this time!" << std::endl;
		//std::cout << "TIME FOR ENTIRE INTERATIONS: "<<  maxNum << std::endl;
	}
	


	return 0;
}
