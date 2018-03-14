/*
 * Aisosa Efemwonkieke
 * minimax.h
 */
#ifndef MINIMAX
#define MINIMAX

#include "logic.h"
#include <vector>
struct Node {
	bool root = false;
	bool winning = false; // if current move order is winning
	int metric = 0;
	bool player_move;
	int x;  // row move
	int y;  // column move
	std::vector<Node*> children;
};

class Minimax {
private:
	int x_bound_;
	int y_bound_;
	int player_;
	int opponent_;
	int max_depth_;
	Node* root_; // for printing purposes
	Node* generate_tree(Logic l, Node* n );
	Node* generate_tree_r(Node* r, int x,
						  int y, Logic l, int depth, bool is_player_turn);
	std::vector<Node*> minimax_tree(Node* root);
	Node* choose_move(std::vector<Node*>);
	int minimax_tree_r(Node* n);
public:
	/*
	 * takes in a Logic instance and a specified player (1 or 2)
	 */
	Minimax(Logic l, int p, int depth) {
	    x_bound_ = l.get_row_size();
		y_bound_ = l.get_column_size();
		player_ = p;
		if (player_ == 1)
			opponent_ = 2;
		if (player_ == 2)
			opponent_ = 1;
		max_depth_ = depth;
	}
	~Minimax() {
		delete root_;
	}
	void play(Logic& l) {
		Node* root = new Node;
		root->root = true;
		root = generate_tree(l, root);
	   	Node* move = choose_move(minimax_tree(root));
		l.play(move->x, move->y, player_);
		root_ = root;
	}
	void print_tree_r(Node* n, int indent);
	void print_tree();
};
void print_node(Node* n);
#endif
