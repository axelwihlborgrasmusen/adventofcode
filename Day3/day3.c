#include <stdio.h>

struct coordinates {
	int x;
	int y;
};

struct coordinates createNewStruct(int x, int y) {
        struct coordinates cord = {
                .x = x, .y=y
        };
	return cord;
}

struct coordinates calculateNewCoordinates(struct coordinates* cablePath, char c, int i, struct coordinate lastPoint) {
switch(c) {
case 'R':
	break; 
		
}
}

int readInput(FILE* file, struct coordinates* cablePath) {

	if(file == NULL){
		printf("Could not open specified file");
		return -1;
	}
	char c;
	int i;
	int steps = 0;	
	int firstCable = 1;

	while(fscanf(file, "%c%d,", &c, &i)>0) {
		if(firstCable == 1) {		
			if(c != '\n'){
				steps++;
			} else {
				firstCable = 0;
			}
		}
	}
	
	cablePath = malloc((steps+1) * sizeOf(coordinates));
	rewindFile(file);

        struct coordinate lastPoint;
	while(fscanf(file, "%c%d,", &c, &i)>0) {
                if(firstCable == 1) {
                        if(c != '\n'){
                        	lastPoint = calculateNewCoordinates(cablePath, c, i, steps, lastPoint);
			} else {
                                firstCable = 0;
                        }
                }
        }
 	
	return 0;	
}

int main() {
	FILE* file = fopen("inputday3.txt", "r");

	struct coordinates* cablePath;
	readInput(file, cablePath);
	struct coordinates cord = {
		.x = 1, .y=1
	};
	free(cablePath);
	return 0;

}
