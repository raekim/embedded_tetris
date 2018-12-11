/* Memory Mapped FND Control Example
FILE : mmap_fnd.c
AUTH : Huins, Inc
HOME : www.huins.com
DATE : 2011.10.17 23:40
MENT : Patch mmap error */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <signal.h>

#define FND_MAP_SIZE 0x1000			/* Mapping Size */
#define FND_PHY_ADDR 0x07000000		/* FND physical address */
#define FND_OFFSET 0x4            /* Fnd Offset from base address (FND_PHY_ADDR)*/
#define FND (*((volatile unsigned int *)(fnd_addr + FND_OFFSET)))

void * fnd_addr;

unsigned int val[] = { 0xf9f9, 0xa4a4, 0xb0b0, 0x9999, 0x9292, 0x8282, 0xd8d8, 0x8080,0x9090 };

// Using Exit signal
int quit = 0;
void quit_signal(int sig) {
		quit = 1;
}


int main (int argc, char *argv[]) {
	int fd;
	static unsigned char fnd;
	int count = 0;
	unsigned int tmp;
	unsigned int dtmp;
	int i;

	/* Mapped Device Open */
	fd = open( "/dev/mem", O_RDWR | O_SYNC );
	if (fd == -1) {
		perror("/dev/mem");
		return -1;
	}

	/* Memory mapping */
	fnd_addr = mmap((void *)0, FND_MAP_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, fd, FND_PHY_ADDR);
	if (fnd_addr == NULL) {
		perror("mmap()");
		return -1;
	}

	/* Signal Start */
	signal(SIGINT, quit_signal );
	printf("\nPress <ctrl+c> to quit.\n\n");

	FND = 0;
	sleep(1);

	// Control routine
	while(!quit) {
//		*((unsigned char *)fnd_addr + FND_OFFSET) = (val[fnd++ % 9]);
		tmp = 0;
		dtmp = (unsigned) count;
		for (i = 3; i >= 0; i--){
			tmp |= (dtmp % 10) << (8*i);
			dtmp /= 10;
		}

		FND = tmp;
		//FND=fnd%10; FND |= (fnd%10)<<8;	
		//FND|=(fnd%10)<<16; FND |= (fnd%10)<<24;	
		//FND= 1; FND|= 2<<8;
		//FND= 0x0201;
//printf("DEBUG: FND=%x, fnd=%d\n", FND, fnd);
		//fnd++;
		count++;
		if (count > 9999)
			count = 0;
			sleep(1);
	}

	FND = 0;
//	*((unsigned char *)fnd_addr + FND_OFFSET) = 0xff;


	/* Memory ummapping */
	if (munmap(fnd_addr, FND_MAP_SIZE) == -1) {
		perror("munmap()");
		return -1;
	}

	close(fd);
	return 0;
} 
