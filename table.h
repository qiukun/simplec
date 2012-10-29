#ifndef TABLE_H
#define TABLE_H

typedef struct tableEntry {
	int symbol;
	char type;
	int location;
} tableEntry;

// return location, return -1 if not
int location(int symbol, char type);
void addentry(int symbol, char type, int loc);

#endif
