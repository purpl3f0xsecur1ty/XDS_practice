#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
Spawns a shell but is unused,
here just for exploitation
*/
void getShell(void) {
	setuid(0);
	system("/bin/sh");
}

/*
Clears all buffers related to
I/O operations.
*/
void init() {
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
}

/*
The vulnerable code that allows for
buffer overflow.
*/
void vuln() {
	char buf[100];
	for(int i=0;i<2;i++) {
		read(0, buf, 0x200);
		printf(buf);
	}
}

/*
Calls init(), prints to the screen,
and calls vuln(). getShell() is not
called.
*/
int main(void) {
	init();
	puts("Hoi boi!");
	vuln();
	return 0;
}