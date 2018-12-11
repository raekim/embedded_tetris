#ifndef IF_SWITCH_DEVICE_H
#define IF_SWITCH_DEVICE_H

#define FPGA_SWITCH_LEN 9

	int start_switch(void);
	void *capture_input_switch(void* arg);
	int run_switch(void);
	int is_empty_switch_que(void);
	int size_switch_que(void);
	int read_switch_que(int *read);
	int end_switch(void);

#endif
