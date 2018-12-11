#ifndef IF_DOT_DEVICE_H
#define IF_DOT_DEVICE_H

#define FPGA_DOT_WIDTH 7
#define FPGA_DOT_HEIGHT 10
#define FPGA_DOT_LEN 10

	int start_dot(void);
	int show_dot(int ar[][FPGA_DOT_WIDTH]);
	int end_dot(void);

#endif
