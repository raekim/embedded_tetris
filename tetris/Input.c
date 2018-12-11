#include "Input.h"
#include <stdio.h>
#include "console.h"
#include "if_fpga_switch.h"

void Input(Game *g) {
	g->last_input = get_user_input();
}

int get_user_input(void) {
	int a;	// 1left 2right 3down 4rotate

#ifdef CONSOLE_MODE
	scanf("%d", &a);
	if (1 <= a && a <= 4)
		return a;
	else
		return -1;
#else
	if (!is_empty_switch_que()){
		read_switch_que(&a);

		switch(a){
		case 3:
			a = 1;
			break;
		case 5:
			a = 2;
			break;
		case 7:
			a = 3;
			break;
		case 8:
			a = 4;
			break;
		default:
			a = -1;
		}
	}
	else
		return -1;
#endif
}