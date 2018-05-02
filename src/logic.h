/*
 * TicTacToe Game Logic
 */
#ifndef LOGIC
#define LOGIC
#include <vector>
#include <cstdio>
#include <cmath>
#include <climits>
#include <fstream>
class Logic {
private:
	char player_one = 'O';
	char player_two = 'X';
	char empty = ' ';
	int row_size;
	int column_size;
	int num_to_win;
	std::vector<std::vector<char>> board;
	bool n_in_a_row();
	bool n_in_a_column();
	// digonal from left to right;
	bool n_in_a_diagonal_left_to_right();
	// digonal from right to left
	bool n_in_a_diagonal_right_to_left();
	// Validity Functions
public:
	int n_in_a_row(int player);
	int n_in_a_column(int player);
	int n_in_a_diagonal_left_to_right(int player);
	int n_in_a_diagonal_right_to_left(int player);
	int max_points(int player) {
		int side = std::max(n_in_a_row(player), n_in_a_column(player));
		int diagonal = std::max(n_in_a_diagonal_left_to_right(player)
						   , n_in_a_diagonal_right_to_left(player));
		return std::max(side, diagonal);
	}
	int get_metric(int player) { // metric in respect to player
		if (max_points(player) == num_to_win) // win
			return INT_MAX;
		int opponent = (player == 1)? 2 : 1;
	    if(max_points(opponent) == num_to_win) // loss
			return INT_MIN;
		return (max_points(player) - max_points(opponent));
				
	}
	// x and y are dimensions of tictacN board and winning_n is the amount 
	// markers in a row needed to win
	Logic(int x, int y, int n) {
		num_to_win = n;
		row_size = x;
		column_size = y;
		init();
	}
	Logic(Logic& l) {
		num_to_win = l.get_num_to_win();
		row_size = l.get_row_size();
		column_size = l.get_column_size();
		board = l.get_board();
	}
	void init();
	void print();
	bool play(int x, int y, int player) {
		if (is_empty(x, y)) {
			board[x][y] = ((player == 1)? player_one : player_two);
			return true;
		}
		return false;
	}
	bool is_valid(int x, int y) {
		return (x < row_size && x >= 0 && y < column_size && y >=0 && is_empty(x, y));
	}
	bool is_board_full();
  
	bool is_empty(int x, int y) {
		return board[x][y] == empty;
	}
	bool is_game_over() {
		int w = num_to_win;
		return (max_points(1) == w) || (max_points(2) == w) || is_board_full();
	}
	bool check_board();
	std::vector<std::vector<char>> get_board() {
		return board;
	}
	int get_num_to_win() {
		return num_to_win;
	}
	int get_row_size() {
		return row_size;
	}
	int get_column_size() {
		return column_size;
	}
	void save(std::string path);
	
};

#endif
