#ifndef UPDATE_H
#define UPDATE_H
#include "GameInfo.h"
void Update(Game *g);
void update_block_info(Game *g);	// 입력을 바탕으로 현재 블록의 최종 좌표 결정
//void add_current_block_to_board(Game *g);	// 현재 블록의 좌표 바탕으로 게임 화면 갱신
//void update_score(Game *g);	// 현재 보드를 바탕으로 점수 계산
//void destroy_blocks(Game *g);	// 삭제 가능한 블록 줄이 있으면 파괴하고 게임보드 갱신
int check_block_info(int ni, int nj, int nr, Game *g);	// 현재 블록의 업데이트 정보가 유효한지 체크 (유효시 1 리턴)
void handle_block_collision(Game *g);	// 현재 블록이 땅에 닿거나 다른 블록 위에 착지했을 경우를 핸들링(다음 블록이 떨어지고, 점수관련 계산 등)
void new_block_falls(Game *g);	// 현재 블록이 다 떨어지고 나서, 다음 블록으로의 정보갱신
void freeze_cur_block(Game *g);	// 현재 블록을 게임판에 고정시킴. 즉, 현재 블록이 배경블록이 되는 것임.
void handle_scoring(Game *g);	// 없앨 수 있는 블록 줄을 인지하고 없앤 후, 게임 배경 갱신하고 점수 추가.


#endif
