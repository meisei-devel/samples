#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

int main(int argc, char **argv) {

	int fd, i; unsigned char reg,arg[2];

	if( (fd = open("/dev/i2c-1", O_RDWR )) < 0) {
		fprintf(stderr, "Faild to open /dev/i2c-1 as fd\n");
		return (-1);
	}

	reg = 0x60;

	if(ioctl(fd, I2C_SLAVE, reg) < 0) {
		fprintf(stderr, "Unable to get bus access to talk to slave 0x%02X\n", reg);
		close(fd);
		return (-1);
	}

	arg[0] = 0x00;
	arg[1] = 0x00;

	if(write(fd, arg, 2) != 2) { /* ALL LED INIT */
		fprintf(stderr, "Error writing to i2c slave %02x %02x\n", arg[0], arg[1]);
		close(fd);
		return (-1);
	}

	arg[0] = 0x17;
	arg[1] = 0xff;

	if(write(fd, arg, 2) != 2) { /* LED4 ON */
		fprintf(stderr, "Error writing to i2c slave %02x %02x\n", arg[0], arg[1]);
		close(fd);
		return (-1);
	}

	for(i = 0; i < 10; i++) {
		arg[0] = 0x0f;
		if(i % 2 == 0) {
			arg[1] = 0x22; /* LED4-R Level 0x22 */
		}
		else {
			arg[1] = 0x00; /* LED4-R Level 0x00(Off) */
		}
		if(write(fd, arg, 2) != 2) {
			fprintf(stderr, "Error writing to i2c slave %02x %02x\n", arg[0], arg[1]);
			close(fd);
			return (-1);
		}
		fprintf(stdout, "%d\n", i + 1);
		sleep(1);
	}

	close(fd);

	return 0;
}
