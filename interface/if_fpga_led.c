#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "if_fpga_led.h"

#define LED_DEVICE "/dev/fpga_led"

static int led_dev = -1;

int start_led(void){
	led_dev = open(LED_DEVICE, O_RDWR);

	return led_dev < 0 ? -1 : 0;
}

int light_led(int ar[][LED_WIDTH]){
	char tmp;
	int i, j;

	tmp = 0;
	for (i = 0; i < LED_HEIGHT; i++)
		for (j = 0; j < LED_WIDTH; j++)
			tmp |= ar[i][j]<<((LED_HEIGHT-1-i) * LED_WIDTH + 
				LED_WIDTH-1  - j);

	if (write(led_dev, &tmp, LED_LEN) < 0)
		return -1;

	return 0;
}

int end_led(void){
	int tmp = 0;

	if (led_dev >= 0)
		tmp = close(led_dev);

	led_dev = -1;

	return tmp;
} 
