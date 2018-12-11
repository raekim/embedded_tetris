#define CONSOLE_MODE	// 콘솔창 테스트용. 디바이스와 연결해서 실행 시 코멘트 처리하세요.

#include "Init.h"
#include "Draw.h"
#include "Input.h"
#include "Update.h"
#include "GameInfo.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	Game game;

	Init(&game);
	/* Game Loop */
	while (game.is_playing) {
		Draw(&game);
		Input(&game);
		Update(&game);
#ifdef CONSOLE_MODE
		system("clear");	// 콘솔 클리어 용. 윈도우환경 실행시 cls, 유닉스 환경 실행시 clear. 최종본에서는 필요없음.
#endif
		// usleep(888)
	}

	return 0;
}
