#ifndef DRAW_H
#define DRAW_H
#include "GameInfo.h"
void Draw(Game *g);
void draw_game_board(Game *g);	// 게임 판을 그린다.
void draw_next_block(Game *g);	// 다음 떨어질 블록 정보를 그린다.
#endif