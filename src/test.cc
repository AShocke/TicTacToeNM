#include <iostream>
#include "logic.h"
#include "minimax.h"
int main() {
	Logic l(3, 3, 3);
	l.play(1, 1, 2);
	l.play(0, 2, 1);
	l.play(2, 0, 1);
	l.play(0, 1, 1);
	l.play(1, 2, 1);
	l.play(0, 0, 1);
	l.print();
	//Minimax m(l, 2, 5);
	//m.play(l);
	//m.print_tree();
	l.print();
	std::cout << l.is_game_over() << " " << l.n_in_a_row(1) << "\n";
}
