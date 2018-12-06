#include "Update.h"
#include "GameInfo.h"
// 블록 회전 시 충돌계산 할 것

void Update(Game *g) {
	
	update_block_info(g);
	//add_current_block_to_board(g);
}

void update_block_info(Game *g) {
	switch (g->last_input) {
	case 1://left
		g->cur_block_j--;
		if (g->cur_block_j < 0)
			g->cur_block_j = 0;
		break;
	case 2://right
		g->cur_block_j++;
		if (g->cur_block_j >= 7)
			g->cur_block_j = 6;
		break;
	case 3://down
		g->cur_block_i++;
		if (g->cur_block_i >= 10)
			g->cur_block_i = 9;
		break;
	case 4://rotate
		g->cur_block_rotate_idx = (g->cur_block_rotate_idx + 1) % 4;
		break;
	default:
		break;
	}

}
/*
void add_current_block_to_board(Game *g) {
	int i, j;
	int block_i, block_j;	// 떨어지고 있는 블록의 좌표

	block_i = g->cur_block_i;
	block_j = g->cur_block_j;

	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (0 <= i + block_i && i + block_i< 10 && 0 <= j + block_j && j + block_j < 7) {
				g->game_board[i + block_i][j + block_j] = blocks[g->cur_block_idx][g->cur_block_rotate_idx][i][j];
			}
		}
	}
}
*/