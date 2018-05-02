/*
 * Game implementation for TicTacToe
 */
#include "minimax.h"
#include "logic.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>

const std::string GAME = "game.txt";
int find_winner(Logic& l) {
	if (l.is_game_over()) {
			if (l.get_metric(1) == INT_MAX) {
				printf("Player one wins\n");
					return 2;
			}
			if (l.get_metric(1) == INT_MIN) {
				printf("Player two wins\n");
				return 1;
			}
			else {
				printf("Draw!\n");
				return 0;
			}
		}
	return -1;
}
bool ai_play(Minimax& ai, Logic& l, int ai_turn) {
	printf("AI turn...\n");
	ai.play(l);
	//ai.print_tree();
	l.print();
			
	if (l.is_game_over()) {
		if (l.get_metric(ai_turn) == INT_MAX) {
		printf("AI wins!\n");
		    return true;
		}
		else {
			printf ("Draw!\n");
			return true;
		}
	}
	return false;
}
bool human_play(Logic& l, int h) {
	printf("Your turn: \n");
		int x, y;
		scanf("%d %d", &x, &y);
		while (!l.is_valid(x, y)) {
			printf("Invalid move try again: ");
			scanf("%d", &y);
		}
		l.play(x, y, h);
		if (l.is_game_over()) {
			l.print();
			if (l.get_metric(h) == INT_MAX) {
				printf("Human player wins!\n");
				return true;
			}
			else {
				printf ("Draw!\n");
				return false;
			}
		}
		return false;
}
void ai_vs_ai(Logic& l) {
	bool play = true;
	while (play) {
		l.init();
		int depth1;
		int depth2;
		printf("AI 1 depth: ");
		scanf("%d", &depth1);
		printf("AI 2 depth: ");
		scanf("%d", &depth2);
		l.print();
		Minimax ai_1(l, 1, depth1);
		Minimax ai_2(l, 2, depth2);
		while(!l.is_game_over()) {
			ai_1.play(l);
			l.print();
			int winner = find_winner(l);
			if (winner == -1) {
				ai_2.play(l);
				l.print();
				winner = find_winner(l);
			}
		}
		char choice;
		printf("Play this mode again? (Y/n): ");
		scanf(" %c", &choice);
		if (!(choice == 'y' || choice == 'Y')) {
			play = false;
			l.save(GAME);
		}
	}
}
void player_vs_ai(Logic& l) {
	bool play = true;
	while (play) {
		l.init();
		int depth;
		printf("AI depth: ");
		scanf("%d", &depth);
		l.print();
		srand(time(NULL));
		int human_turn = rand() % 3;
		printf("human_turn: %d\n", human_turn);
		bool is_human_turn = (human_turn == 1)? true : false;
		int ai_turn = (human_turn == 1)? 2 : 1;
		Minimax ai(l, ai_turn , depth);
		while(!l.is_game_over()) {
			if (is_human_turn) {
				human_play(l, human_turn);
				is_human_turn = false;
			}
			else {
				ai_play(ai, l, ai_turn);
				is_human_turn = true;
			}

		}
		char choice;
		printf("Play this mode again? (Y/n): ");
		scanf(" %c", &choice);
		if (!(choice == 'y' || choice == 'Y'))
			play = false;
	}

}

int main() {
	bool play = true;
	while (play) {
		printf("Specifiy board dimensions: ");
		int x, y;
		scanf("%d %d", &x, &y);
		int w;
		printf("How many counters in a row to win? ");
		scanf("%d", &w);
		Logic l(x, y, w);
		printf("What mode?: ");
		char choice;
		scanf(" %c", &choice);
		if (choice == 'a')
			ai_vs_ai(l);
		if (choice == 'p')
			player_vs_ai(l);
		if (choice == 'q')
			return 0;
		printf("Play again? (Y/n): ");
		scanf(" %c", &choice);
		if (!(choice == 'y' || choice == 'Y'))
			play = false;
	}
}
