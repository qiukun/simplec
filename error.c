#include <stdio.h>
#include <stdlib.h>

void perr(const char *str) {
	fputs(str, stderr);
}

void err_memoryfull() {
	perr("MEMORY IS FULL");
	exit(EXIT_FAILURE);
}
