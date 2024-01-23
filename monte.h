#pragma once
#include "node.h"

class MonteCarloTreeSearch {
public:
	friend class MCTSNode;
	MonteCarloTreeSearch(double c_param); 
	~MonteCarloTreeSearch();
	int search(Connect4Board board); // gimme back best move
	int firstSearch(Connect4Board board); // for our first search
private:
	int player_to_move = 1;
	Connect4Board board;
	int depth = 100;
	int _how_deep = 1; // how deep did the tree grow
	double c_param = 1;
	vector<Node*> all_nodes;
	Node* selection(Node* node);
	Node* expansion(Node* node);
	double rollout(Node* node);
	void backpropagate(Node* node, double score);
	Node* ucb1(Node* node);
	Node* most_visited_node(Node* node); // pass parent node as an agrument and it returns child with most visits
	Node* most_scoring_node(Node* node); // pass parent node as an agrument and it returns child with most visits
};
