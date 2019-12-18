#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct coordinates {
	int x;
	int y;
};

struct coordinates createNewCord(int x, int y) {
	struct coordinates cord = {
		.x = x, .y=y
	};
	return cord;
}

struct coordinates calculateNewCoordinates(char c, int i, struct coordinates lastPoint) {
	struct coordinates newCord;
	switch(c) {
		case 'R':
			newCord = createNewCord((lastPoint.x + i), lastPoint.y);
			break;
		case 'L':
			newCord = createNewCord((lastPoint.x - i), lastPoint.y);
			break;
		case 'U':
			newCord = createNewCord(lastPoint.x, (lastPoint.y + i));
			break;
		case 'D':
			newCord = createNewCord(lastPoint.x, (lastPoint.y - i));
			break;	
	}
	return newCord;
}

int calculateClosestIntersect(struct coordinates* cablePath, struct coordinates from, struct coordinates to) {

	//calculate if there is an intersection here and return the length to that, else return max_int

	return 0;
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
			if(c != '\n'){
				steps++;
			} else {
				goto nextStep;
			}
	}
	nextStep:
	cablePath = malloc((steps+1) * sizeof(struct coordinates));
	rewind(file);

	struct coordinates lastPoint = createNewCord(0,0);
	struct coordinates newPoint = createNewCord(0,0);
	int step = 0;	
	cablePath[step] = lastPoint;
	int closestIntersect = INT_MAX;
	int intersect = INT_MAX;	

	while(fscanf(file, "%c%d,", &c, &i)>0) {
		if(firstCable == 1) {
			if(c != '\n'){
				step++;
				lastPoint = calculateNewCoordinates(c, i, lastPoint);
				cablePath[step] = lastPoint;
			} else {
				firstCable = 0;
				lastPoint = createNewCord(0,0);
			}
		} else {
			newPoint = calculateNewCoordinates(c, i, lastPoint);
			intersect = calculateClosestIntersect(cablePath, lastPoint, newPoint);
			if(intersect < closestIntersect) {
				closestIntersect = intersect;
			}
			lastPoint = newPoint;
		}
	}

	return closestIntersect;	
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
