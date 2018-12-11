#ifndef IF_SWITCH_DEVICE_H
#define IF_SWITCH_DEVICE_H

#define FPGA_SWITCH_LEN 9

	int start_switch(void);
	void *capture_input_switch(void* arg); // 쓰레드 호출용
	int run_switch(void);		// 쓰레드 사용
	int is_empty_switch_que(void);	// 눌린 인풋 큐 비었나
	int size_switch_que(void);		// 눌린 인풋 큐 크기 
	int read_switch_que(int *read);	// 눌린 인풋 큐에서 가져오기
	int end_switch(void);

#endif
