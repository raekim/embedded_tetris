#include "Init.h"
#include <stdlib.h>
void Init(Game *g) {
	time_t t;
	srand((unsigned)time(&t));
	g->is_playing = 1;
	g->score = 0;
	g->cur_block_idx = rand() % 7;
	g->cur_block_rotate_idx = 0;
	g->cur_block_i = 0;
	g->cur_block_j = 4;
	g->last_input = -1;
	init_game_board(&(g->game_board));
	g->next_block_idx = rand() % 7;
}

void init_game_board(int (*board)[7]) {
	int i, j;
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 7; ++j) {
			board[i][j] = 0;
		}
	}
}