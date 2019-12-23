#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

struct coordinates {
	int x;
	int y;
	int step;
};

struct coordinates createNewCord(int x, int y, int step) {
	struct coordinates cord = {
		.x = x, .y=y, .step = step
	};
	return cord;
}

struct coordinates calculateNewCoordinates(struct coordinates* path, char c, int i, struct coordinates lastPoint, int* pos) {
	struct coordinates newCord = createNewCord(lastPoint.x, lastPoint.y, lastPoint.step);
	int stop = *pos + i;
	for(;*pos < stop; (*pos)++) {
		newCord.step++;
		switch(c) {
			case 'R':
				newCord.x++;
				break;
			case 'L':
				newCord.x--;
				break;
			case 'U':
				newCord.y++;	
				break;
			case 'D':
				newCord.y--;
				break;	
		}
		path[*pos] = newCord;
	}
	return newCord;
}

int compare(const void* a, const void* b) {
	struct coordinates first = *(struct coordinates*) a;
	struct coordinates second = *(struct coordinates*) b;
	return (abs(first.x) + abs(first.y)) - (abs(second.x) + abs(second.y));
}

int calculateClosestIntersect(struct coordinates* cablePath, struct coordinates* cablePath2, int size1, int size2) {

	qsort(cablePath, size1, sizeof(struct coordinates), compare);
	qsort(cablePath2, size2, sizeof(struct coordinates), compare);
	int step = INT_MAX;
	int jj = 0;
	for(int i = 0; i < size1; i++) {
		for(int j = jj; j < size2; j++) {
			struct coordinates firstCord = cablePath[i];
			struct coordinates secondCord = cablePath2[j];
			if (compare( &firstCord, &secondCord) < 0) {
				break;
			} else if (compare( &firstCord, &secondCord) > 0) {
				jj = j + 1;
				continue;	
			}
			if(firstCord.step > step || secondCord.step > step || (firstCord.step + secondCord.step) > step) {
				continue;
			}
			if(firstCord.x == secondCord.x && firstCord.y == secondCord.y) {
				if(step > (firstCord.step + secondCord.step)) {
					step = (firstCord.step + secondCord.step);
				}
			}
		}
	}

	return step;
}

int readInput(FILE* file, struct coordinates* cablePath, struct coordinates* cablePath2) {
	if(file == NULL){
		printf("Could not open specified file");
		return -1;
	}
	char c;
	int i;
	int stepsCable1 = 0;
	int stepsCable2 = 0;	
	int firstCable = 1;
	while(fscanf(file, "%c%d,", &c, &i)>0) {
		if(firstCable == 1) {
			if(c != '\n'){
				stepsCable1 += i;
			} else {
				firstCable = 0;
			}
		} else {
			stepsCable2 += i;
		}
	}
	cablePath = malloc((stepsCable1) * sizeof(struct coordinates));
	cablePath2 = malloc((stepsCable2) * sizeof(struct coordinates));
	rewind(file);
	firstCable = 1;
	struct coordinates lastPoint = createNewCord(0,0, 0);
	int step = 0;


	while(fscanf(file, "%c%d,", &c, &i)>0) {
		if(firstCable == 1) {
			if(c != '\n'){
				lastPoint = calculateNewCoordinates(cablePath, c, i, lastPoint, &step);
			} else {
				firstCable = 0;
				lastPoint = createNewCord(0,0,0);
				step = 0;
			}
		} else {
			lastPoint = calculateNewCoordinates(cablePath2, c, i, lastPoint, &step);
		}
	}
	return calculateClosestIntersect(cablePath, cablePath2, stepsCable1, stepsCable2);
}

int main() {
	FILE* file = fopen("inputday3.txt", "r");

	struct coordinates* cablePath;
	struct coordinates* cablePath2;
	int closest = readInput(file, cablePath, cablePath2);
	printf("%d", closest);
	free(cablePath);
	free(cablePath2);

	return 0;
}
