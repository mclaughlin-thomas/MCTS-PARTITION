#include "node.h"

Node::Node(Connect4Board board) {
	this->board = board;
	this->parent = nullptr;
	this->parent_action = NULL; // stay null
	this->player_to_move = this->board.getTurn();
	this->untried_actions = this->board.legal_moves();
	this->_is_fully_expanded = check_if_fully_expanded();
	this->_is_terminal_state = check_if_terminal_state();
}

Node::~Node() {

}

Node& Node::operator=(const Node& n) {
	//copy node vals, this is first time using operator overloading
	this->board = n.board;
	this->parent = n.parent;
	this->parent_action = n.parent_action;
	this->player_to_move = this->board.getTurn();
	this->untried_actions = this->board.legal_moves();
	this->_is_fully_expanded = this->check_if_fully_expanded();
	this->_is_terminal_state = this->check_if_terminal_state();
	this->visits = n.visits;
	this->score = score;
	this->ucb1 = n.ucb1;
	this->untried_actions = n.untried_actions;
	this->children = n.children;
	return *this;
}

Node::Node(Connect4Board board, Node* par, int parMov) {
	this->board = board;
	this->parent = par;
	this->parent_action = parMov;
	this->player_to_move = this->board.getTurn();
	this->untried_actions = this->board.legal_moves();
	this->_is_fully_expanded = check_if_fully_expanded();
	this->_is_terminal_state = check_if_terminal_state();
}

Node::Node(const Node& n) {
	//dc stuff
	this->board = n.board;
	this->parent = n.parent;
	this->parent_action = n.parent_action;
	this->player_to_move = n.player_to_move;
	this->untried_actions = n.untried_actions;
	this->_is_fully_expanded = n._is_fully_expanded;
	this->_is_terminal_state = n._is_terminal_state;
	this->visits = n.visits;
	this->score = score;
	this->ucb1 = n.ucb1;
	this->untried_actions = n.untried_actions;
	this->children = n.children;
}

bool Node::check_if_fully_expanded() {
	return (untried_actions.size() == 0);
}

bool Node::check_if_terminal_state() {
	return board.terminalOutcome();
}
