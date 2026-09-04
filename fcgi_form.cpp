#include <string.h>
#include <stdint.h>
#include <stdlib.h>
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

		char *ptr,*mem = NULL; size_t len = 0,frn;

		if( (ptr = getenv( "QUERY_STRING" )) != NULL && (len = strlen( ptr )) > 0 ){
			FCGI_printf("GET Parameter String :\n");
			mem = strdup( ptr );
		}
		else if( (ptr = getenv( "CONTENT_LENGTH" )) != NULL && (len = atoi( ptr )) > 0 ){
			FCGI_printf("POST Parameter String :\n");
			if( (mem = (char*)malloc( len + 1 )) != NULL ){
				frn = FCGI_fread( mem,len,1,FCGI_stdin );
				mem[len] = '\0';
			}
		}

		if (mem) {
			FCGI_fwrite( mem,len,1,FCGI_stdout );
			FCGI_printf("\n");
			free(mem);
		}
	}

	return 0;
}
