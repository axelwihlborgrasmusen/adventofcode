#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct planet {
	char* name[4];
	struct planet* parent;
	struct planet* orbiters;
	int orbiterSize;
};

struct inputValue {
	char* name[4];
	char* orbit[4];
	int handled;
};


int createNewPlanet(struct planet* planets, char* name, char* orbiter) {
	
	if(strcmp(name, "COM") == 0) {
		struct planet COM = {
			.name = name;
			.parent = NULL;
			.orbiters = malloc(sizeof(struct planet);
			.orbiterSize = 1;
		};
		struct planet child = {
			.name = orbiter;
			.parent = COM;
			.orbiters = NULL;
			.orbiterSize = 0;
		};
		com.orbiters[0] = child;
		return 1;	
	}	
		
	for(int i = 0; i < sizeof(planets); i++) {
		if(strcmp(planets[i].name, name) == 0) {
			//parent planet found!
			struct planet parent = planets[i];
			struct planet child = {
				.name = name
				.parent = parent;
				.orbiters = NULL;
				.orbiterSize = 0;
			}
			if(parent.orbiterSize == 0) {
				parent.orbiter = malloc(sizeof(planets);
				parent.orbiter[0] = child;
				parent.orbiterSize++;
			} else {
				struct planet* temp = malloc(parent.orbiterSize + 1);
				for(int t = 0; t< orbiterSize; t++) {
					temp[t] = parent.orbiter[t];
				}
				temp[parent.orbiterSize] = child;
				parent.orbiter = temp;	
			}
			return 1;			
		}
	}	
	return 0;
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
	char name[4];
	char orbiter[4];
	struct inputValue value = {
			.name = NULL;
			.orbit = NULL;
			.handled = 0;	
		}
	int count = 0;
	while(fscanf(file, "%c%c%c)%c%c%c\n",&name[0], &name[1], &name[2], &orbiter[0], &orbiter[1], &orbiter[2])>0) {
		value.name = name;
		value.orbit = orbiter;		
		in[count] = value;
		count++;			
	}
}

int cmp (const void * a, const void * b) {
	struct inputValue first = *(struct inputValue*) a;
   	struct inputValue second = *(struct inputValue*) b;
	return (b.handled - a.handled);
}

void fixPlanets(struct inputValue* in, strict planet* planets, int length) {
	int done = 0;
	redo:
	for(int i = done; i < sizeof(in); i++) {
		struct inputValue current = in[i];
		if(createNewPlanet(current.name, current.orbit) == 1) {
			done++;
			current.handled
		}	
	}

	qsort(in, length, sizeof(inputValue), cmp);
	goto redo;
}

int main() {
	FILE* file;
	file = fopen("inputday6.txt", "r");
	int length = calculateRows(file);
	struct inputValue* in = malloc(length*sizeof(struct inputValue));
	struct planet* planets = malloc(length*sizeof(struct planet));
	readInput(file, in);
	fixPlanets(in, planets, length);
	printf("Length: %d", length);
	return 0;
}
