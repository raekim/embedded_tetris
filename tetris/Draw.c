#include "Draw.h"
#include <stdio.h>
#include "if_fpga_dot.h"
#include "console.h"

#ifdef CONSOLE_MODE
	#define STAR ('*')
	#define BLANK ('.')
#else
	#define STAR (1)
	#define BLANK (0)
#endif

void Draw(Game *g) {
	draw_game_board(g);
}

void draw_game_board(Game *g) {
	int draw_board[10][7];	// 실제 그릴 보드
	char c;
	int i, j;
	int block_i, block_j;	// 떨어지고 있는 블록의 좌표

	// 배경 그림을 실제 그릴 보드에 복사
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 7; ++j) {
			c = (g->game_board[i][j] == 1)? STAR : BLANK;
			draw_board[i][j] = c;
		}
	}

	// 떨어지는 블록 그림을 실제 그릴 보드에 복사
	block_i = g->cur_block_i;
	block_j = g->cur_block_j;

	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (0 <= i + block_i && i + block_i< 10 && 0 <= j + block_j && j + block_j < 7) {
				c = (blocks[g->cur_block_idx][g->cur_block_rotate_idx][i][j] == 1) ? STAR : BLANK;
				if(c == STAR)
					draw_board[i + block_i][j + block_j] = c; 
			}
		}
	}
#ifdef CONSOLE_MODE
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 7; ++j) {
			printf("%c", draw_board[i][j]);
		}
		printf("\n");
	}
#else
	show_dot(draw_board);
#endif
}

void draw_next_block(Game *g) {

}
