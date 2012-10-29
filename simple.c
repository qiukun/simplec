#include <stdio.h>
#include "table.h"
#include "error.h"

#define MAXN 100

void firstpass(in) {
	char line[MAXN];
	int ic, id;

	while (fgets(line, MAXN, in) != NULL) {
		if (ic < id) {
			addentry(atoi(strtok(line, delim)), 'L', ic);
		} else {
			err_memoryfull();
		}

		tok = strtok(NULL, delim);
		if (!tok) break;
		if (strcmp("rem", tok) == 0) 
			break;
		if (strcmp("input", tok) == 0) {
			tok = strtok(NULL, delim);
			i = lookup(tok[0]);
			if (i == -1) {
				addentryV(tok[0]);
				insertcode(get_value(READ, id));
			} else {
				if (ic > id) {
					return MEMORYFULLERR;
				}
				insertcode(get_value(READ, table[i].location));
			}
		}
		if (strcmp("let", tok) == 0) {
			struct node in[LENGTH], post[LENGTH];
			int j;

			tok = strtok(NULL, delim);
			i = lookup(tok[0]);
			if (i == -1) {
				addentry(tok[0], 'V', id);
				id--;
			}
			strtok(NULL, delim); // discard '='

			// build in
			j = 0;
			while ((tok = strtok(NULL, delim)) != NULL) {
				in[j++] = toktonode(tok);
			}
			intopost(in, j, post);
			posttosml();
		}
		if (strcmp("print", tok) == 0) {
			tok = strtok(NULL, delim);
			i = lookup(tok[0]);
			insertcode(get_value(WRITE, table[i].location));
		}
		if (strcmp("goto", tok) == 0) {
		}
		if (strcmp("if", tok) == 0) {
		}
		if (strcmp("end", tok) == 0) {
			insertcode(get_value(HALT, 0));
		}
	}
}

void secondpass()
{
	int loc; // Location
	for (i = 0; i < MEMORYSIZE; i++) {
		if (flag[i] != -1) {
			loc = lookup(flag[i], 'L');
			memory[i] += loc;
		}
	}
}


int main(int argc, char *argv[]) {
	FILE *in, *out;	

	if (argc > 1) {
		in = fopen(argv[1], "r");
	} else {
		in = fopen("in.simple", "r");
	}
	if (argc > 2) {
		out = fopen(argv[2], "w");
	} else {
		out = fopen("out.sml", "w");
	}

	firstpass(in);
	secondpass();
	output();

	return 0;
}
