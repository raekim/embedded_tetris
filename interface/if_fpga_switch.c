#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "if_fpga_switch.h"
#include "que.h"

#define FPGA_SWITCH_DEVICE "/dev/fpga_push_switch"

static int switch_dev = -1;

static int is_end;
static Que que;

static pthread_t thread_id;
static pthread_mutex_t que_mutex, end_mutex;


int start_switch(void){
	switch_dev = open(FPGA_SWITCH_DEVICE, O_RDWR);

	is_end = 0;
	init_que(&que);

	pthread_mutex_init(&que_mutex, NULL);
	pthread_mutex_init(&end_mutex, NULL);

	return switch_dev < 0 ? -1 : 0;
}

// 처음으로 버튼이 눌렸을 때 큐에 저장함
// 000011111110000111
//     ^          ^
// 저기 둘이 버튼 눌린것으로 생각

// 입력 받을시 입력 사이 시간이 짧으면 입력이 불안정함
// 예시) 8번 버튼 누르면 0번 버튼에 입력이 있다고 나오는 경우
// 안정적인 입력이 받게 하면 입력을 빠르게 받기 불가능
// 그래서 짧은 입력을 여러번 받아서
// 눌린 상태가 5번 나와야 버튼이 눌린것으로 해석
// 눌린 버튼은 무조건 눌렸다고 나오는거 같아서
// 5번 수치 조정해도 될듯
void *capture_input_switch(void* arg){
	unsigned char cur[FPGA_SWITCH_LEN];
	int cnt[FPGA_SWITCH_LEN];
	int i;

	memset(cnt, 0, sizeof(cnt));

	pthread_mutex_lock(&end_mutex);
	while (!is_end){
		pthread_mutex_unlock(&end_mutex);

		read(switch_dev, &cur, sizeof(cur));

		for (i = 0; i < FPGA_SWITCH_LEN; i++){
			if (cur[i] == 0)
				cnt[i] = 0;
			else{
				cnt[i]++;
				if (cnt[i] == 5){
					pthread_mutex_lock(&que_mutex);

					push_que(&que, i);

					pthread_mutex_unlock(&que_mutex);
				}
			}
		}

		usleep(1000);

		pthread_mutex_lock(&end_mutex);
	}

	pthread_mutex_unlock(&end_mutex);

	clear_que(&que);

	return 0;
}

// 쓰레드 실행
int run_switch(void){
	return pthread_create(&thread_id, NULL, capture_input_switch, NULL) == 0 ? 0 : -1;
}

int is_empty_switch_que(void){
	int ret;

	pthread_mutex_lock(&que_mutex);

	ret = is_empty_que(&que);

	pthread_mutex_unlock(&que_mutex);

	return ret;
}

int size_switch_que(void){
	int ret;

	pthread_mutex_lock(&que_mutex);

	ret = size_que(&que);

	pthread_mutex_unlock(&que_mutex);

	return ret;
}

int read_switch_que(int *read){
	int error_state;

	pthread_mutex_lock(&que_mutex);

	error_state = pop_que(&que, read);

	pthread_mutex_unlock(&que_mutex);

	return error_state;
}

// 쓰레드에 종료 요청 후 쓰레드 종료시 함수 종료
int end_switch(void){
	int tmp, tmp2;

	pthread_mutex_lock(&end_mutex);
	is_end = 1;
	pthread_mutex_unlock(&end_mutex);

	tmp = pthread_join(thread_id, NULL);

	pthread_mutex_destroy(&que_mutex);
	pthread_mutex_destroy(&end_mutex);
	
	if (switch_dev >= 0)
		tmp2 = close(switch_dev);
	switch_dev = -1;

	return tmp == 0 && tmp2 == 0 ? 0 : -1;
} 
