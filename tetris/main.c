#include "console.h"
#include "Init.h"
#include "Draw.h"
#include "Input.h"
#include "Update.h"
#include "GameInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	Game game;

	block_signals();
	Init(&game);
	/* Game Loop */;
	while (game.is_playing) {
		Draw(&game);
		Input(&game);
		/* 1프레임 증가 */
		usleep(1000);	// 1000 microsecond = 0.001 second
		Update(&game);
#ifdef CONSOLE_MODE
		system("clear");	// 콘솔 클리어 용. 윈도우환경 실행시 cls, 유닉스 환경 실행시 clear. 최종본에서는 필요없음.
#endif
		
	}

	Quit(&game);

	return 0;
}
