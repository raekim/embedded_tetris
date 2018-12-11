#include "Init.h"
#include <time.h>
#include <stdlib.h>

/* 게임 객체 초기화 */
void Init(Game *g) {
	time_t t;
	srand((unsigned)time(&t));	// 랜덤 시드 설정
	/* 각각의 필드 정보 설명은 Gameinfo.h의 typedef struct Game 선언부 참조하세요 */
	g->is_playing = 1;
	g->score = 0;	
	g->cur_block_idx = rand() % 7;
	g->cur_block_rotate_idx = 0;
	g->cur_block_i = -2;
	g->cur_block_j = 3;
	g->last_input = -1;
	init_game_board(g->game_board);
	g->next_block_idx = rand() % 7;
	g->cur_frame = 0;
}

/* 게임 보드 초기화 */
void init_game_board(int (*board)[7]) {
	int i, j;
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 7; ++j) {
			board[i][j] = 0;
		}
	}
}
