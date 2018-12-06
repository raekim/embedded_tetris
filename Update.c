#include "Update.h"
#include "GameInfo.h"
// 블록 회전 시 충돌계산 할 것

void Update(Game *g) {
	
	update_block_info(g);
	//add_current_block_to_board(g);
}

void update_block_info(Game *g) {
	int new_i, new_j;	// 업데이트 후의 블록 좌표 정보
	int new_rot;	// 업데이트 후의 블록 회전 정보

	new_i = g->cur_block_i;
	new_j = g->cur_block_j;
	new_rot = g->cur_block_rotate_idx;

	switch (g->last_input) {
	case 1://left
		new_j = g->cur_block_j-1;
		break;
	case 2://right
		new_j = g->cur_block_j + 1;
		break;
	case 3://down
		new_i = g->cur_block_i + 1;
		break;
	case 4://rotate
		new_rot = (g->cur_block_rotate_idx + 1) % 4;
		break;
	default:
		break;
	}

	// 변경된 블록 정보에 따라 블록을 이동 및 회전해도 괜찮은지 확인 후 업데이트
	// 화면 벗어남, 배경 블록들과 충돌 여부 체크
	if (check_block_info(new_i, new_j, new_rot, g) == 1) {
		// 괜찮다고 확인 한 후에야 업데이트
		g->cur_block_i = new_i;
		g->cur_block_j = new_j;
		g->cur_block_rotate_idx = new_rot;
	}
}

int check_block_info(int ni, int nj, int nr, Game *g) {
	int i, j;

	// 블록이 화면을 벗어나는지 체크
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			// 그려야 하는 부분(숫자 1로 표현)이 10X7 화면에서 벗어나면 안 됨
			if (blocks[g->cur_block_idx][nr][i][j] == 1) {
				if (i + ni < 0 || i + ni >= 10 || j + nj < 0 || j + nj >= 7)
					return 0;
				else {
					// 블록이 기존 블록들과 겹치면 안 됨
					if (g->game_board[i + ni][j + nj] == 1)
						return 0;
				}
			}
		}
	}

	// 모든 기준을 통과했으므로 합격임(1 리턴)
	return 1;
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