#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include "fcgi_config.h"
#include "fcgi_stdio.h"

int main (void) {
	uint32_t access_counter = 0;

	while (FCGI_Accept() >= 0) {

		FCGI_printf("Content-type: text/plain\r\n"
		"\r\n"
		"Hello World! Access Counter : %ld\n",
		++access_counter);

	}
	return 0;
}
