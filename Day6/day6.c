#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct inputValue {
	char name[4];
	char orbit[4];
	int hand;
};


int calculateRows(FILE* file) {
	char name[4];
	char orbiter[4];

	int count = 0;
	while(fscanf(file, "%c%c%c)%c%c%c\n",&name[0], &name[1], &name[2], &orbiter[0], &orbiter[1], &orbiter[2])>0) {
		count++;
	}
	rewind(file);
	return count;
}

void readInput(FILE* file, struct inputValue* in) {
	char input[10] = {0};
	struct inputValue value = {
		.name = "NUL",
		.orbit = "NUL",
		.hand = 0
	};
	int count = 0;
	while(fscanf(file, "%s\n",input)>0) {
		strncpy(value.name, strtok(input, ")"), 4);
		strncpy(value.orbit, strtok(NULL, ")"), 4);
		in[count] = value;
		count++;			
	}
}

void printPlanets(struct inputValue* in, int len) {
	for(int i = 0; i < len; i++) {
		printf("%s)%s \n", in[i].name, in[i].orbit);
	}
}

int done(struct inputValue* in, int len) {
	for(int i = 0; i < len; i++) {
		if(in[i].hand == 0) {
			return 0;
		}
	}
	return 1;
}

void calculateOrbits(struct inputValue* in, int len) {
	int dir = 0;
	int indir = 0;

	char (*curr)[4] = malloc(len/3 * sizeof(char) * 4);
	char (*next)[4] = malloc(len/3 * 4);

	int nCounter = 0;
	int clen = 1;
	int level = 0;
	strncpy(curr[0], "COM", 4);

	while(!done(in, len) && level < 2350) {
		for(int i = 0; i<clen; i++) {
			for(int j = 0; j<len; j++) {
				if(strcmp(in[j].name, curr[i]) == 0) {
					in[j].hand = 1;
					strncpy(next[nCounter], in[j].orbit, 4);
					nCounter++;
				}			
			
			}		
		}
		clen = nCounter;
		nCounter = 0;
		dir += clen;
		level++;
		indir += (clen * (level));
		memcpy(curr, next, len/3);
		memset(next, 0, len/3);
	}
	printf("Direct: %d, Indirect: %d, Sum: %d", dir, indir, dir+indir);
}

int main() {
	FILE* file;
	file = fopen("inputday6.txt", "r");
	int length = calculateRows(file);
	struct inputValue* in = malloc(length*sizeof(struct inputValue));
	readInput(file, in);
	calculateOrbits(in, length);
	printf("End of program");
	return 0;
}
