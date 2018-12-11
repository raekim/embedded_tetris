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

void *capture_input_switch(void* arg){
	unsigned char cur[FPGA_SWITCH_LEN];
	int cnt[FPGA_SWITCH_LEN];
	int i;

	memset(cnt, 0, sizeof(cnt));

	pthread_mutex_lock(&end_mutex);
	while (!is_end){
		pthread_mutex_unlock(&end_mutex);
/*
for (i = 0; i < FPGA_SWITCH_LEN; i++)
printf("%d ", cur[i]);
printf("\n");
*/
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
//		usleep(100000);

		pthread_mutex_lock(&end_mutex);
	}

	pthread_mutex_unlock(&end_mutex);

	clear_que(&que);

	return 0;
}

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
