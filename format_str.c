#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int target;

void shell() {
	system("/bin/sh");
}

void deadcode() {
	char *information = "The execution flow was redirected";
	printf(information);
	_exit(1);
}

void vuln() {
	char buffer[512];
	fgets(buffer, sizeof(buffer), stdin);
	printf(buffer);
	exit(1);
}

int main(int argc, char **argv) {
	vuln();
}