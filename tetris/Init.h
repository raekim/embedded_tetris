#ifndef INIT_H
#define INIT_H
#include "GameInfo.h"
void Init(Game *g);
void init_game_board(int (*board)[7]);
void block_signals(void);
void Quit(Game *g);

#endif