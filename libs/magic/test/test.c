#include <stdio.h>
#include "magic.h"

int main(void)
{
	printf("1\n");
	char *actual_file = "test.pdf";
	const char *magic_full;
	magic_t magic_cookie;
	/*MAGIC_MIME tells magic to return a mime of the file, but you can specify different things*/
	printf("2\n");
	//magic_cookie = magic_open(MAGIC_MIME_TYPE); //Only Mime
	magic_cookie = magic_open(MAGIC_MIME_ENCODING); //Only charset
	//magic_cookie = magic_open(MAGIC_MIME); //Mime + charset
	//magic_cookie = magic_open(MAGIC_NONE); 
	printf("3\n");

	if (magic_cookie == NULL) {
		printf("unable to initialize magic library\n");
		return 1;
	}
	printf("4\n");

	printf("Loading default magic database\n");

	if (magic_load(magic_cookie,"magic.mgc") != 0) {
		printf("cannot load magic database - %s\n", magic_error(magic_cookie));
		magic_close(magic_cookie);
		return 1;
	}
	printf("5\n");
	
	magic_full = magic_file(magic_cookie, actual_file);
	printf("%s\n", magic_full);
	
	magic_setflags(magic_cookie,MAGIC_MIME_TYPE);
	magic_full = magic_file(magic_cookie, actual_file);
	printf("%s\n", magic_full);	
	
	magic_setflags(magic_cookie,MAGIC_MIME);
	magic_full = magic_file(magic_cookie, actual_file);
	printf("%s\n", magic_full);	
	
	magic_setflags(magic_cookie,MAGIC_NONE);
	magic_full = magic_file(magic_cookie, actual_file);
	printf("%s\n", magic_full);			
	
	magic_close(magic_cookie);
        return 0;
}