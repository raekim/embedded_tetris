#include "Update.h"
#include "GameInfo.h"
#include <stdlib.h>
#include "console.h"
// 블록 회전 시 충돌계산 할 것

void Update(Game *g) {
	g->cur_frame += 1;		// 프레임 증가
	
	update_block_info(g);	// 사용자 인풋에 따라 블록 움직임

	if(g->cur_frame == 100){	// 1초당 자동으로 블록 떨어짐 처리
		g->cur_block_i += 1;
		g->cur_frame = 0;	// 프레임 초기화
	}

	handle_block_collision(g);	// 블록이 땅에 닿거나 다른 블록 위에 떨어지면 알맞은 작업 수행
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

void handle_block_collision(Game *g) {
	int i, j;

	// 블록이 땅에 닿았나? 혹은 다른 블록의 위에 착지하는 상황인가?
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (blocks[g->cur_block_idx][g->cur_block_rotate_idx][i][j] == 1) {
				// 블록이 땅에 착지하는 상황
				if (g->cur_block_i + i == 9) {
					// 블록 얼어붙게 만들기(게임보드에 고정)
					freeze_cur_block(g);
					// 다음 블록으로 갱신
					new_block_falls(g);
				}
				// 블록이 다른 블록의 위에 착지하는 상황
				// 블록이 사용자 인풋에 의하여 기존 블록과 겹치는 일은 발생하지 않으므로(예외처리), 겹친다는 것은 자동적으로 떨어짐에 의한 것임. 인덱스를 하나 위로 올린 다음 얼어붙게 해야 함(그렇지 않으면 진짜 겹쳐버리기 때문에)
				else if (g->game_board[g->cur_block_i + i][g->cur_block_j + j] == 1) {
					// 블록을 한 칸 올린 후 얼어붙게 만들기
					g->cur_block_i--;
					freeze_cur_block(g);
					// 다음 블록으로 갱신
					new_block_falls(g);
				}
			}
		}
	}

	// 점수 계산 함수 호출. 점수 득점이 가능한가 확인하고 점수 변경
}

void new_block_falls(Game *g) {
	g->cur_block_idx = g->next_block_idx;	// 다음 블록이 현재 블록이 된다.
	g->cur_block_rotate_idx = 0;	// 처음 회전 정보로 초기화
	// 블록의 시작 좌표 초기화
	g->cur_block_i = -2;
	g->cur_block_j = 3;

	// 새로운 '다음 블록'이 랜덤하게 설정됨.
	g->next_block_idx = rand() % 7;
}

void freeze_cur_block(Game *g) {
	int i, j;
	int block_i = g->cur_block_i;
	int block_j = g->cur_block_j;
	char c;

	// 게임판에 현재 블록을 각인시킴(현재 블록이 배경 블록이 된다)
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (0 <= i + block_i && i + block_i< 10 && 0 <= j + block_j && j + block_j < 7){
				if (blocks[g->cur_block_idx][g->cur_block_rotate_idx][i][j] == 1) {
					g->game_board[i + block_i][j + block_j] = blocks[g->cur_block_idx][g->cur_block_rotate_idx][i][j];
				}
			}
		}
	}
}
