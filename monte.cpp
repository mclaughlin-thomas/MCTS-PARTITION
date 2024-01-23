#include "monte.h"
#include <fstream>
#include <cstdlib>



MonteCarloTreeSearch::MonteCarloTreeSearch(double c_param) {
	this->c_param = c_param;

}
MonteCarloTreeSearch::~MonteCarloTreeSearch() {

}

int MonteCarloTreeSearch::search(Connect4Board board) {
	_how_deep = 0;
	all_nodes.clear();


	if (board.getTurn() == -1) {
		board.invert();
		this->board = board;
		//this->depth = depth;		done recently
		this->player_to_move = board.getTurn();
	}

	this->board = board;
	//this->depth = depth;			done recently
	this->player_to_move = board.getTurn();

	Node* root = new Node(this->board);
	all_nodes.push_back(root);

	double score = 0;

	int counter = 0;




	//int counter = 0;
	int  counterr = 0;
	auto start = std::chrono::steady_clock::now();

	do {
		//auto innerStart = std::chrono::steady_clock::now(); //maybe remove auto?
		Node* node = selection(root);
		//.std::cout<< "selection completed"<<std::endl;
		//auto end = std::chrono::steady_clock::now();
		//auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
		
		score = rollout(node);
		//std::cout<< "rollout completed"<<std::endl;
		//end = std::chrono::steady_clock::now();
		//elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
		
		backpropagate(node, score);
		//std::cout<< "backpropogate completed"<<std::endl;
		//end = std::chrono::steady_clock::now();
		//elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
		//auto end = std::chrono::steady_clock::now();
		/*if (end < quickestIteration) {
			quickestIteration = end;
		}
		if (end > slowestIteration) {
			slowestIteration = end;
		}*/

		//counter++;
		counterr++;
	} while (counterr< TIME);
	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::ofstream outputFile("timing_results.txt", std::ios::app); // Open a file for writing

	outputFile << "Board size " << COLS << ". Selection completed in " << elapsed << " ms" << std::endl;

	outputFile.close(); // Close the file
	std::cout<<"Board size " << COLS<<"\ Written to file!"<<std::endl;
	exit(0);
	//std::cout<< "Counter: " << counter << std::endl;
	//using namespace std::chrono_literals;
	//std::this_thread::sleep_for(3s); // remove for testing


	Connect4Board nTemp_board = this->board;
	nTemp_board.make_move(most_scoring_node(root)->parent_action);

	



	return most_scoring_node(root)->parent_action;
	//return this->most_visited_node(root)->parent_action;
}




Node* MonteCarloTreeSearch::most_visited_node(Node* node) {

	vector<Node*> temp;
	temp.clear();
	int temp_visits = 0;

	for (auto& child : node->children) {
		if (child->visits > temp_visits) {
			temp_visits = child->visits;
			temp.clear();
			temp.push_back(child);
		}
		else if (child->visits == temp_visits) {
			temp.push_back(child);

		}
	}

	int random_index = rand() % temp.size();

	return temp[random_index];
}

Node* MonteCarloTreeSearch::most_scoring_node(Node* node) {

	vector<Node*> temp;
	temp.clear();
	int temp_score = -999999;

	for (auto& child : node->children) {
		if (child->score > temp_score) {
			temp_score = child->score;
			temp.clear();
			temp.push_back(child);
		}
		else if (child->score == temp_score) {
			temp.push_back(child);

		}
	}
	if (temp.size() == 0) {
		//we lost :(
		exit(-1);
	}
	int random_index = rand() % temp.size();

	return temp[random_index];
}



Node* MonteCarloTreeSearch::selection(Node* node) {
	_how_deep = 1;

	while (node->_is_terminal_state == false) {
		//if (_how_deep > 3) { // 3 used on mcts board of 7x6 but 10000 on 10kx10k, but those are not def vals, 7x6 zooms n 3 should display too deep. 10kx10k does not zoom, like every few seconds couts, but never goes inside if
		//	std::cout << "too deep!?" << std::endl;
		//	return node;
		//}
		if (node->_is_fully_expanded == false) {
			return expansion(node);
		}
		else {
			node = ucb1(node);
			_how_deep++;
		}
	
		_how_deep++; // once more because we just selected another node, counting root as deep=0;
	}
	return node;
}

Node* MonteCarloTreeSearch::expansion(Node* node) {



	int action = node->untried_actions.back(); // get last element
	node->untried_actions.pop_back(); // remove this element as it is now 'tried' action
	Connect4Board new_board(node->board);
	new_board.make_move(action);
	Node* child_node = new Node(new_board, node, action);
	node->children.push_back(child_node);
	node->_is_fully_expanded = node->check_if_fully_expanded();

	all_nodes.push_back(child_node);

	return child_node;
}

double MonteCarloTreeSearch::rollout(Node* node) { //aid changes made here
	/*
	TODO: implement counting how many moves before outcome and return multiplied value
	that will favour moves that win quickly, but also avoid losing quickly
	*/
	int moves_count = 0;
	Connect4Board rollout_board(node->board);
	while (!rollout_board.terminalOutcome()) {
		//if(moves_count > 10000){
		//	std::cout<<"Exiting babay girl\n\n uh" << std::endl;
		//	return (static_cast<double>(((player_to_move == rollout_board.result() ? 1.f : 10.f)) * 10.f / (1 + moves_count)) * rollout_board.result()); // definitely needs reworded
		//}
		//something here makes this take like 3 seconds on every iteration of while loop when massive like 10kx10k
		vector<int> untried = rollout_board.legal_moves();

		int random_index = rand() % untried.size();

		int action = untried[random_index];
		untried.erase(untried.begin() + random_index);
		rollout_board.make_move(action);
		moves_count++;
		untried.clear();
	} 

	//
	// x^-1 function gives higher\lower values for quick wins/loses
	// statement ? 1.f : 5.f  -- loses are worse than missed wins
	return (static_cast<double>(((player_to_move == rollout_board.result() ? 1.f : 10.f)) * 10.f / (1 + moves_count)) * rollout_board.result()); // definitely needs reworded
}

void MonteCarloTreeSearch::backpropagate(Node* node, double score) {
	node->visits++;

	node->score += score;

	if (node->parent != nullptr) {
		backpropagate(node->parent, score);
	}

}

Node* MonteCarloTreeSearch::ucb1(Node* node) {

	vector<Node*> best_moves;
	best_moves.clear();
	double best_score = -999999;
	double c_param = this->c_param;
	double move_score;

	for (auto& child : node->children) {
		move_score = child->score / child->visits + c_param * sqrt(log(node->visits) / child->visits);

		if (move_score > best_score) {
			best_score = move_score;
			best_moves.clear();
			best_moves.push_back(child);
		}
		else if (move_score == best_score) {
			best_moves.push_back(child);
		}

	}
	int random_index;
	if (best_moves.size() != 0) {
		random_index = rand() % best_moves.size();
	}
	else {
		random_index = 0;
		cout << "else" << endl;
	}

	return best_moves[random_index];
}
