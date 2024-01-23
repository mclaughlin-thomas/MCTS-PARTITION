#include "globals.h"
#include "connectboard.h"

class Node {
public:
	friend class MonteCarloTreeSearch;
	Node(Connect4Board board);
	~Node();
	Node(const Node& n);
	Node& operator=(const Node& n);
	Node(Connect4Board board, Node* par, int parMov);
private:
	Connect4Board board;
	Node* parent = nullptr;
	int action;
	int parent_action;
	int player_to_move;
	int visits = 0;
	double score = 0;
	double ucb1 = 0;
	vector<int> untried_actions;
	vector<Node*> children;
	bool _is_fully_expanded;
	bool _is_terminal_state;
	bool check_if_fully_expanded();
	bool check_if_terminal_state();
};
