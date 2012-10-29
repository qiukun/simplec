#include <stdio.h>
#include "sml.h"
#include "memory.h"

#define ZEROERR 1
#define UNVALIDOPCODE 2
#define ACCOVERFLOW 3

// Registers
static int acc, // Accumulator
	   inscnt, // Instruction counter
	   insreg, // Instruction register
	   opcode, // Operation code
	   oprand; // Oprand

void welcome() {
	printf("Welcome to Simpletron\n");
}

void input(int hasinputfile) {
	int i, t;

	for (i = 0; i < MEMORYSIZE; i++) {
		if (!hasinputfile) {
			printf("%d", i);
		}
		scanf("%d", &t);
		if (t == -99999) break;
		memory[i] = t;
	}
}

void dump() {
	int i;

	printf("acc:%d\n", acc);
	printf("inscnt:%d\n", inscnt);
	printf("insreg:%d\n", insreg);
	printf("opcode:%d\n", opcode);
	printf("oprand:%d\n", oprand);
	for (i = 0; i < MEMORYSIZE; i++) {
		printf("%d: %d\n", i, memory[i]);
	}
}

int sim(){
	int s; // Temp var for overflow checking

	while (1) {
		insreg = memory[inscnt];
		opcode = get_opcode(insreg);
		oprand = get_oprand(insreg);

		switch (opcode) {
			case 0:
				break;
			case READ:
				printf("input %d:", oprand);
				scanf("%d", &memory[oprand]);
				break;
			case WRITE:
				printf("%d\n", memory[oprand]);
				break;
			case LOAD:
				acc = memory[oprand];
				break;
			case STORE:
				memory[oprand] = acc;
				break;
			case ADD:
				s = acc + memory[oprand];
				if (s>9999 || s<-9999) return ACCOVERFLOW;
				acc = s;
				break;
			case SUBSTRACT:
				s = acc - memory[oprand];
				if (s>9999 || s<-9999) return ACCOVERFLOW;
				acc -= memory[oprand];
				break;
			case DEVIDE:
				if (memory[oprand] == 0) return ZEROERR;
				acc /= memory[oprand];
				break;
			case MULTIPLY:
				acc *= memory[oprand];
				break;
			case BRANCH:
				inscnt = oprand-1;
				break;
			case BRANCHNEG:
				if (acc < 0)
					inscnt = oprand-1;
				break;
			case BRANCHZERO:
				if (acc == 0)
					inscnt = oprand-1;
				break;
			case HALT:
				return 0;
			default:
				return UNVALIDOPCODE;
		}
		inscnt++;
	}
}

int main(int argc, char *argv[]) {
	int r;

	welcome();

	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	}
	if (argc == 3) {
		freopen(argv[2], "w", stdout);
	}
	input(argc > 1);

	freopen("/dev/tty", "r", stdin);
	r = sim();
	switch(r) {
		case 0:
			break;
		case ZEROERR:
			printf("Attempt to divided by zero");
			break;
		case UNVALIDOPCODE:
			printf("OPCODE IS UNVALID");
			break;
		case ACCOVERFLOW:
			printf("Accumulator overflow");
			break;
	}
	dump();

	return 0;
}

