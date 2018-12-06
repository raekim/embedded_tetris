#ifndef UPDATE_H
#define UPDATE_H
#include "GameInfo.h"
void Update(Game *g);
void update_block_info(Game *g);	// 입력을 바탕으로 현재 블록의 최종 좌표 결정
//void add_current_block_to_board(Game *g);	// 현재 블록의 좌표 바탕으로 게임 화면 갱신
//void update_score(Game *g);	// 현재 보드를 바탕으로 점수 계산
//void destroy_blocks(Game *g);	// 삭제 가능한 블록 줄이 있으면 파괴하고 게임보드 갱신

#endif