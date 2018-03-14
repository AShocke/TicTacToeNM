/*
 * MiniMax implementation
 */
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "minimax.h"
#include "limits.h"


Node* Minimax::generate_tree(Logic l, Node* root) {
	for (int i = 0; i < x_bound_; i++) {
		for (int j = 0; j < y_bound_; j++) {
			if (l.is_empty(i, j)) {
				Node* child = new Node;
				child = generate_tree_r(child, i, j, l, 0, true);
				root->children.push_back(child);
			}
		}
	}
	return root;
}
Node* Minimax::generate_tree_r(Node* r, int x, int y,
							   Logic l, int depth, bool is_player_turn) {
	int player = (is_player_turn? player_ : opponent_);
	if (depth == max_depth_) {
		r->player_move = is_player_turn;
		r->x = x;
		r->y = y;
		l.play(x, y, player);
		r->metric = l.get_metric(player_); // always in the ai's eyes
		return r;
	}
	r->player_move = is_player_turn;
	r->x = x;
	r->y = y;
	l.play(x, y, player);
	r->metric = l.get_metric(player_); // always in the ai's eyes
	if (l.is_game_over()) {
		return r;
	}
	else {
		for (int i = 0; i < x_bound_; i++ ){
			for (int j = 0; j < y_bound_; j++) {
				if (l.is_empty(i, j)) {
					Node* child = new Node;
					child = generate_tree_r(child, i, j, l,
											depth + 1, !is_player_turn);
					r->children.push_back(child);
				}
			}
		}
	}
	return r;
}
std::vector<Node*> Minimax::minimax_tree(Node* root) {
	std::vector<Node*> optimal;
	int best = INT_MIN;
	printf("children size: %ld\n", root->children.size());
	for (int i  = 0; i < root->children.size(); i++) {
		int curr = minimax_tree_r(root->children[i]);
//		printf("current :%d\n", curr);
		if (curr > best) {
			optimal.clear();
			optimal.push_back(root->children[i]);
			best = curr;
		}
		else if (curr == best) {
			optimal.push_back(root->children[i]);
		}
	}
	printf("optimal children size: %ld best value: %d\n", optimal.size(), best);
	for (int i = 0; i < optimal.size(); i++) {
		print_node(optimal[i]);
	}
	return optimal;
}

int Minimax::minimax_tree_r(Node* root) {
	if (root->children.size() == 0)
		return root->metric;
	if (root->player_move) {
		int best = INT_MAX;
		for (int i = 0; i < root->children.size(); i++) {
			best = std::min(best, minimax_tree_r(root->children[i]));
		}
//					printf("maximizing best: %d\n", best);
		return best;
	}
	else {
		int best = INT_MIN;
		for (int i = 0; i < root->children.size(); i++) {
			best = std::max(best, minimax_tree_r(root->children[i]));
		
		}
//			printf("minimizing best: %d\n", best);
		return best;
	}
}
// chooses a move randomly based on optimal choices
Node* Minimax::choose_move(std::vector<Node*> b) {
	srand(time(NULL));
	int x = rand() % b.size();
	return b[x];
}
void Minimax::print_tree() {
	print_tree_r(root_, 0);
	std::cout << max_depth_ << "\n";
}
void print_node(Node* n) {
	printf("(%d %d): %d\n", n->x, n->y, n->metric);
}
void Minimax::print_tree_r(Node* n, int indent) {

	if (n->children.size() == 0) {
		std::cout << std::setw (indent) << (n->player_move? "P (" : "O (")
	              << n->x << ", " << n->y <<  ", "
				  << n->metric << ")\n";
		return;
	}
	else {
		if (n->root) {
			std::cout << std::setw(indent) << "R\n";
		}
		else {
			std::cout << std::setw (indent) << (n->player_move? "P (" : "O (")
					  << n->x << ", " << n->y <<  ", "
					  << n->metric << ")\n";
		}
		for (int i = 0; i < n->children.size(); i++) {
			print_tree_r(n->children[i], indent + 5);
		}
	}
}

