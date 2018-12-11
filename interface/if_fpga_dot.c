#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "if_fpga_dot.h"

#define FPGA_DOT_DEVICE "/dev/fpga_dot"

static int dot_dev = -1;

int start_dot(void){
	dot_dev = open(FPGA_DOT_DEVICE, O_RDWR);

	return dot_dev < 0 ? -1 : 0;
}

int show_dot(int ar[][FPGA_DOT_WIDTH]){
	unsigned char tmp[FPGA_DOT_HEIGHT];
	int i, j;


	memset(tmp, 0, sizeof(tmp));
	for (i = 0; i < FPGA_DOT_HEIGHT; i++)
		for (j = 0; j < FPGA_DOT_WIDTH; j++)
			tmp[i] |= ar[i][j]<<(FPGA_DOT_WIDTH-1-j);

	if (write(dot_dev, &tmp, FPGA_DOT_LEN) < 0)
		return -1;

	return 0;
}

int end_dot(void){
	int tmp = 0;

	if (dot_dev >= 0)
		tmp = close(dot_dev);

	dot_dev = -1;
	
	return tmp;
} 
