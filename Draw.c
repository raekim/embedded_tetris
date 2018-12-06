﻿#include "Draw.h"
#include <stdio.h>
void Draw(Game *g) {
	draw_game_board(g);
}

void draw_game_board(Game *g) {
	int draw_board[10][7];	// 실제 그릴 보드
	char c;
	int i, j;
	int block_i, block_j;	// 떨어지고 있는 블록의 좌표

	// 배경 그림
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 7; ++j) {
			c = (g->game_board[i][j] == 1)? '*' : '.';
			draw_board[i][j] = c;
		}
	}

	// 떨어지는 블록 그림
	block_i = g->cur_block_i;
	block_j = g->cur_block_j;

	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (0 <= i + block_i && i + block_i< 10 && 0 <= j + block_j && j + block_j < 7) {
				c = (blocks[g->cur_block_idx][g->cur_block_rotate_idx][i][j] == 1) ? '*' : '.';
				if(c == '*')
					draw_board[i + block_i][j + block_j] = c; 
			}
		}
	}

	// 최종 그림
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 7; ++j) {
			printf("%c", draw_board[i][j]);
		}
		printf("\n");
	}
}

void draw_next_block(Game *g) {

}