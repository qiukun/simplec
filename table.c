#include "table.h"
#define TN 10000

static tableEntry table[TN];
static int it = 0;

int location(int symbol, char type)
{
	int i;
	for (i = 0; i < TN; i++) {
		if (table[i].symbol == symbol && table[i].type == type) {
			return table[i].location;
		}
	}
	return -1;
}

void addentry(int symbol, char type, int loc)
{
	table[it] = (struct tableentry){symbol, type, loc};
	it++;
}

