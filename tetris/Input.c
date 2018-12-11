#include "Input.h"
#include <stdio.h>
#include "console.h"

void Input(Game *g) {
	g->last_input = get_user_input();
}

int get_user_input(void) {
	int a;	// 1left 2right 3down 4rotate
	scanf("%d", &a);
	if (1 <= a && a <= 4)
		return a;
	else
		return -1;
}