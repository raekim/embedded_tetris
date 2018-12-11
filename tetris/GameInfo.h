#ifndef GAMEINFO_H
#define GAMEINFO_H

extern int blocks[7][4][4][4];

typedef struct Game {
	int is_playing;			// 현재 게임이 실행중인가? 아닌가?
	int score;				// 현재 점수
	int cur_block_idx;		// 현재 내려오고 있는 블록의 인덱스(0-6)
	int cur_block_rotate_idx;	// 현재 내려오고 있는 블록의 회전 인덱스(0-3)
	int cur_block_i, cur_block_j;	// 현재 내려오고 있는 블록의 위치 좌표(i,j)
	int last_input;			// 제일 최근에 받은 사용자 입력 정보(왼쪽,오른쪽,아래,회전 중 하나)
	int game_board[10][7];		// 현재 게임 보드 (떨어지고 있는 블록 제외한 배경, 1또는 0)	
	int next_block_idx;		// 다음 내려올 블록 인덱스(0-6)
}Game;


#endif
