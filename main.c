#include "Draw.h"
#include "Input.h"
#include "Update.h"
#include "GameInfo.h"
#include <stdio.h>
#include <conio.h>

int main(void) {
	Game game;

	Init(&game);
	/* Game Loop */
	while (game.is_playing) {
		Draw(&game);
		Input(&game);
		Update(&game);
		system("cls");	// 콘솔 클리어 용. 윈도우환경 실행시 cls, 유닉스 환경 실행시 clear. 최종본에서는 필요없음.
		// usleep(888)
	}

	return 0;
}