#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct inputValue {
	char name[4];
	char orbit[4];
	int hand;
};

struct parent {
	char name[4];
	int len;
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

void populateparents(struct inputValue* in, struct parent* par, int len) {
	int position = 0;
	struct parent p = {
		.name = "STR",
		.len = 0
		};
	
		while (strcmp(par[position].name, "COM") != 0) {
			for(int i = 0; i < len; i++) {
				if(strcmp(in[i].orbit, par[position].name) == 0) {
					position++;
					strncpy(p.name, in[i].name, 4);
					p.len++;
					par[position] = p;
				}
		}	

}
}

int intersect(struct parent* me, struct parent* san, int len) {
	
	for(int i = 1; i < len; i++) {
		for(int j = 1; j < len; j++) {
			if(strcmp(me[i].name, san[j].name) == 0) {
				return me[i].len + san[j].len - 2;
			}
		}
	}

	return -1;
}

void calculateOrbits(struct inputValue* in, int len) {
	int dir = 0;
	int indir = 0;

	struct parent* me = malloc(len/3 * sizeof(struct parent) * 4);
	struct parent*  san = malloc(len/3 * 4 * sizeof(struct parent));
	
	struct parent t = {
		.name = "YOU",
		.len = 0
		};
	me[0] = t;
	strncpy(t.name, "SAN", 4);
	san[0] = t;
	populateparents(in, me, len);
	populateparents(in, san, len);
	int jump = intersect(me, san, len/3);
	printf("Totalt len is: %d", jump);
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
