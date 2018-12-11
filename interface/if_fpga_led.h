#ifndef IF_LED_DEVICE_H
#define IF_LED_DEVICE_H

#define LED_WIDTH 4
#define LED_HEIGHT 2
#define LED_LEN 1

	int start_led(void);
	int light_led(int ar[][LED_WIDTH]);
	int end_led(void);

#endif
