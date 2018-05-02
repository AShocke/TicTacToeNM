/*
 * Logic class implementation for tictactoe
 * logic.cc
 */
#include "logic.h"
#include <iostream>
#include <fstream>
/*
 * Constructors
 */ 
Logic::Logic(std::string path) {
	std::ifstream f;
	f.open(path);
	if (f.is_open()) {
		f >> num_to_win;
		f >> row_size >> column_size;
		for (int i = 0; i < row_size; i++) {
			for (int j = 0; j < column_size; j++) {
				f >> board[i][j];
			}
		}
		f.close();
	}
	else {
		file_error_msg(path);
	}
}

/*
 * Conditions
 */
bool Logic::is_board_full() {
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < column_size; j++) {
			if (is_empty(i, j)) {
				return false;
			}
		}
	}
	return true;
}
bool Logic::n_in_a_row() {
	char marker_in_a_row = ' ';
	int max_in_a_row = 0;
	for (int i = 0; i < row_size; i++) {
		int same_in_a_row = 0;
		for (int j = 0; j < column_size; j++) {
			if(same_in_a_row == num_to_win) 
					return true;
			if (!is_empty(i, j)) {
				char curr_marker = board[i][j];
				if (curr_marker == marker_in_a_row) {
					same_in_a_row++;
					marker_in_a_row = curr_marker;
				}
				else {
					same_in_a_row = 0;
					marker_in_a_row = curr_marker;
				}
			}
			if (same_in_a_row > max_in_a_row) {
				max_in_a_row = same_in_a_row;
			}
		}
	}
	return (max_in_a_row == num_to_win);
}

bool Logic::n_in_a_column() {
	char marker_in_a_row = ' ';
	int same_in_a_row = 0;
	for (int i = 0; i < column_size; i++) {
		for (int j = 0; j < row_size; j++) {
			if (!is_empty(j, i)) {
				char curr_marker = board[j][i];
				if(same_in_a_row == num_to_win) 
					return true;
				if (curr_marker == marker_in_a_row) {
					same_in_a_row++;
					marker_in_a_row = curr_marker;
				}
				else {
					same_in_a_row = 0;
					marker_in_a_row = curr_marker;
				}
			}
		}
	}
	return false;
}

bool Logic::n_in_a_diagonal_left_to_right() {
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < column_size; j++) {
			if (!is_empty(i, j)) {
				char curr_color = board[i][j];
				int x = i - 1;
				int y = j + 1;
				bool same_color = true;
				int matches = 1;
				while(x >= 0 && y < column_size && same_color) {
					if (board[x][y] != curr_color) {
						same_color = false;
					}
					else {
						matches++;
					}
					x--;
					y++;
				}
				if (matches == num_to_win) {
					return true;
				}
			}
		}
	}
	return false;
}
			
		
bool Logic::n_in_a_diagonal_right_to_left() {
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < column_size; j++) {
			if (!is_empty(i, j)) {
				char curr_color = board[i][j];
				int x = i + 1;
				int y = j + 1;
				bool same_color = true;
				int matches = 1;
				while(x < row_size && y < column_size && same_color) {
					if (board[x][y] != curr_color) {
						same_color = false;
					}
					else {
						matches++;
					}
					x++;
					y++;
				}
				if (matches == num_to_win) {
					return true;
				}
			}
		}
	}
	return false;
}
/*
 * Counting pieces
 */

int Logic::n_in_a_row(int player) {
	char marker_in_a_row = ((player == 1)? player_one : player_two);
	int max_in_a_row = 0;
	for (int i = 0; i < row_size; i++) {
		int same_in_a_row = 0;
		for (int j = 0; j < column_size; j++) {
			char curr_marker = board[i][j];
			if (curr_marker == marker_in_a_row) {
				same_in_a_row++;
			}
			else {
				same_in_a_row = 0;
			}
			if (max_in_a_row < same_in_a_row)
		 		max_in_a_row = same_in_a_row;
		}
	}
	return max_in_a_row;
}

int Logic::n_in_a_column(int player) {
	char marker_in_a_row = ((player == 1)? player_one : player_two);
	int max_in_a_row = 0;
	for (int i = 0; i < column_size; i++) {
		int same_in_a_row = 0;
		for (int j = 0; j < row_size; j++) {
					char curr_marker = board[j][i];
   				if (curr_marker == marker_in_a_row) {
					same_in_a_row++;

				}
				else {
					same_in_a_row = 0;
				}
				if (max_in_a_row < same_in_a_row)
					max_in_a_row = same_in_a_row;
		}
	}
	return max_in_a_row;
}

int Logic::n_in_a_diagonal_left_to_right(int player) {
	int max_matches = 0;
	char player_color = ((player == 1)? player_one : player_two);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < column_size; j++) {
			if (!is_empty(i, j) && board[i][j] == player_color) {
				int x = i - 1;
				int y = j + 1;
				bool same_color = true;
				int matches = 1;
				while(x >= 0 && y < column_size && same_color) {
					if (board[x][y] != player_color) {
						same_color = false;
					}
					else {
						matches++;
						if (matches > max_matches) {
							max_matches = matches;
						}
					}
					x--;
					y++;
				}
			}
		}
	}
	return max_matches;
}
			
		
int Logic::n_in_a_diagonal_right_to_left(int player) {
	int max_matches = 0;
	char player_color = ((player == 1)? player_one : player_two);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < column_size; j++) {
			if (!is_empty(i, j) && board[i][j] == player_color) {
				int x = i + 1;
				int y = j + 1;
				bool same_color = true;
				int matches = 1;
			while(x < row_size && y < column_size && same_color) {
					if (board[x][y] != player_color) {
						same_color = false;
					}
					else {
						matches++;
						if (matches > max_matches) {
							max_matches = matches;
						}
					}
					x++;
					y++;
				}
			}
		}
	}
	return max_matches;
}

/*
 *
 */
void Logic::init() {
	board.clear();
	std::vector<char>col;
	for (int i = 0; i < column_size; i++) {
		col.push_back(empty);
	}
	for (int i = 0; i < row_size; i++) {
		board.push_back(col);
	}
}
void print_line(int length) {
	for (int i = 0; i < length; i++) {
		printf("_");
	}
	printf("\n");
}
void Logic::print() {
	int line_length = 4 * column_size; // amount of characters per line
	printf("\t");
	for (int n = 0; n < column_size; n++) {
		printf("| %d ", n); // there are 4 characters printed per cycle 
	}
	printf("|\n\t");
	print_line(line_length); // loop for each character in a cycle

	printf("\n");
	
	for (int i = 0; i < row_size; i++) {
		printf("%d|\t", i);
		for (int j = 0; j < column_size; j++) {
		   	printf("| %c ", board[i][j]);
		}
		printf("|\n\t");
		print_line(line_length );
	}
	printf("\n");
}

/*
 * File IO saving files
 */
void Logic::save(std::string path) {
	std::ofstream o;
	o.open(path);
	if (o.is_open()) {
		o << num_to_win << "\n";
		o << row_size << " " << column_size << "\n";
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[0].size(); j++) {
				o << board[i][j] << " ";
			}
			o << "\n";
		}
		o.close();
	}
	else {
		file_error_msg(path);
	}
}
