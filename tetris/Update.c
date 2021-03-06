﻿#include "Update.h"
#include "GameInfo.h"
#include <stdlib.h>
#include "console.h"
#define LINE_SCORE 50	// 없어지는 블록 라인 당 점수

void Update(Game *g) {
	g->cur_frame += 1;		// 프레임 증가
	
	update_block_info(g);	// 사용자 인풋에 따라 블록 움직임

	if(g->cur_frame == 300){	// 자동으로 블록 떨어짐 처리
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
		// 블록 위에 떨어지기
		if (check_block_info(new_i, new_j, new_rot, g) == 0){
			freeze_cur_block(g);
			new_block_falls(g);
			return;
		}
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
			// 그려야 하는 부분(숫자 1로 표현)이 10X7 화면에서 왼쪽, 오른쪽을 벗어나면 안 됨
			if (blocks[g->cur_block_idx][nr][i][j] == 1) {
				if (j + nj < 0 || j + nj >= 7)
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

	// 블록이 땅에 닿았나? 혹은 다른 블록의 위에 착지하는 상황인가? ( 땅에 닿는 것을 맨 밑 칸이 아니라 맨 밑 칸을 벗어나는 것으로 설정)
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (blocks[g->cur_block_idx][g->cur_block_rotate_idx][i][j] == 1) {
				// 블록이 땅에 착지하는 상황
				if (g->cur_block_i + i > 9) {
					// 블록을 한 칸 올린 후 얼어붙게 만들기(게임보드에 고정)
					g->cur_block_i--;
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
	handle_scoring(g);
}

void new_block_falls(Game *g) {
	g->cur_block_idx = g->next_block_idx;	// 다음 블록이 현재 블록이 된다.
	g->cur_block_rotate_idx = 0;	// 처음 회전 정보로 초기화
	// 블록의 시작 좌표 초기화
	g->cur_block_i = -2;
	g->cur_block_j = 3;

	// 새로운 '다음 블록'이 랜덤하게 설정됨.
	g->next_block_idx = rand() % 7;

	// determining game over
	if(check_block_info(g->cur_block_i, g->cur_block_j, g->cur_block_rotate_idx, g) == 0){
		g->is_playing = 0;	// stop playing the game
	}
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

// 현재 게임 판을 라인 별로 확인해서 스코어를 계산하고, 게임보드 갱신
//
void handle_scoring(Game *g){
	int score_line_num = 0;	// number of lines to destroy
	int i,j,t;
	int ni;
	int flag = 0;	// is this line all 1s?
	int score_line;	 // 없애야 할 라인
	int new_board[10][7];	// game board after calculating scores

	// initialize new game board
	init_game_board(new_board);

	// copy the existing game board while tallying score_line_num
	ni = 9;
	for(i=9; i>=0; --i){	// start from bottom line
		flag = 1;
		for(j=0; j<7; ++j){
			new_board[ni][j] = g->game_board[i][j];
			if(g->game_board[i][j] == 0)
				flag = 0;
		}
		if(flag == 1){	// score!
			score_line_num++;
		}
		else
			ni--;
	}

	// update the game board
	for(i=0; i<10; ++i){
		for(j=0; j<7; ++j)
			g->game_board[i][j] = new_board[i][j];
	}

	// update score
	g->score += score_line_num*LINE_SCORE;
	if(score_line_num > 0){
		// code for playing buzzer
	}

	// 공중에 떠 있는 조각들 바닥으로 보내기
	/*
	for(i=8; i>=0; --i){
		for(j=0; j<7; ++j){
			if(g->game_board[i][j] == 1 && g->game_board[i+1][j] == 0){	// 공중에 떠 있는 조각 발견
				t = i;
				while(g->game_board[t+1][j] == 0){	// 조각 내리기
					g->game_board[t+1][j] = g->game_board[t][j];
					g->game_board[t][j] = 0;
					t++;
				}
			}
		}
	}
	*/
}
