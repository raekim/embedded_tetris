#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FND_DEVICE "/dev/fpga_fnd"

static int fnd_dev = -1;

int start_fnd(void)
{
	fnd_dev = open(FND_DEVICE, O_RDWR);
	if (fnd_dev < 0)
	{
		printf("Device open error : %s\n", FND_DEVICE);
		exit(1);
	}

	return fnd_dev < 0 ? -1 : 0;
}



int end_fnd(void) {
	int tmp = 0;

	if (fnd_dev >= 0)
		tmp = close(fnd_dev);

	return tmp;
}



int score_fnd(int score)
{
	unsigned char data[4];
	int i;
	
	if (score < 0 || score >= 10000)
		return -1;

	memset(data, 0, sizeof(data));

	for (i=3; score>0; i--)
	{
		data[i] = score % 10;
		score = score / 10;
	}
	write(fnd_dev, &data, 4);

	return 0;
}