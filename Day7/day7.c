#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void readInput(FILE* file, int* input) {
	int temp;
	int count = 0;
	while(fscanf(file, "%d,", &temp)>0) {
		input[count] = temp;
		count++;
	}
	rewind(file);
}



int countInts(FILE* file) {
	char temp;
	int count = 0;
	if(file == NULL){
		printf("Could not open specified file");
		return -1;
	}
	while(fscanf(file,"%c",&temp) != EOF){
		if(temp == ',') {
			count++;
		}
	}
	rewind(file);
	return count - 1;  

}

int runCalc(int* input, int len, int powersetting, int fromPrev) {
	int position = 0;
	int op;
	int firstValue;
	int secondValue;
	int storeAt;
	int mode1;
	int mode2;
	int mode3;

	int firstMode3 = 1;

	//input[1] = noun;
	//input[2] = verb;

	while ( (position - 2) < len)  {

		op = input[position];
		mode3 = op / 10000;
		mode2 = (op / 1000) % 10;
		mode1 = (op / 100) % 10;
		op = op % 100;		
		switch(op) {
			case 1:
				firstValue = mode1 > 0 ? input[position + 1] : input[input[position + 1]];
				secondValue = mode2 > 0 ? input[position + 2] : input[input[position + 2]];
				input[input[position + 3]] = firstValue + secondValue;
				position += 4;
				break;
			case 2:		
				firstValue = mode1 > 0 ? input[position + 1] : input[input[position + 1]];
				secondValue = mode2 > 0 ? input[position + 2] : input[input[position + 2]];
				input[input[position + 3]] = firstValue * secondValue;
				position += 4;
				break;
			case 3:
				printf("Insert input: \n");
				if(mode1 > 0) {
					input[position + 1] = firstMode3 ? powersetting : fromPrev;
					//scanf("%d", &(input[position + 1]));
				} else {		
					input[input[position + 1]] = firstMode3 ? powersetting : fromPrev;
					//scanf("%d", &(input[input[position + 1]]));
				}
				position += 2;
				firstMode3 = 0;
				break;
			case 4:
				if(mode1 > 0) {
					return input[position + 1];
					//printf("%d \n", input[position + 1]);
				} else {
					return input[input[position + 1]];
					//printf("%d \n", input[input[position + 1]]);
				}
				position += 2;
				break;
			case 5:
				firstValue = mode1 > 0 ? input[position + 1] : input[input[position + 1]];
				secondValue = mode2 > 0 ? input[position + 2] : input[input[position + 2]];
				position = firstValue != 0 ? secondValue : position + 3;
				break;
			case 6:
				firstValue = mode1 > 0 ? input[position + 1] : input[input[position + 1]];
				secondValue = mode2 > 0 ? input[position + 2] : input[input[position + 2]];
				position = firstValue == 0 ? secondValue : position + 3;
				break;
			case 7:
				firstValue = mode1 > 0 ? input[position + 1] : input[input[position + 1]];
				secondValue = mode2 > 0 ? input[position + 2] : input[input[position + 2]];
				input[input[position + 3]] = firstValue < secondValue ? 1 : 0;
				position += 4;
				break;
			case 8:
				firstValue = mode1 > 0 ? input[position + 1] : input[input[position + 1]];
				secondValue = mode2 > 0 ? input[position + 2] : input[input[position + 2]];
				input[input[position + 3]] = firstValue == secondValue ? 1 : 0;
				position += 4;
				break;
			case 99:
				printf("OP 99, program halted. Final value: %d \n", input[0]);
				return 0;
		}
		if (position -1  > len) {
			printf("Position cuasing segfault \n");
			return 0;
		}
	}
	return input[0];
}

void swap(int* x, int* y) 
{ 
	int temp;
	temp = *x; 
	*x = *y; 
	*y = temp; 
} 

int permute(int (*perms)[5], int pos, int* seq, int start) {

	int stop = 4;

	if( start == stop) {
		memcpy(perms[pos], seq, 5*sizeof(int));
		pos++; 
	}	

	for(int i = start; i < stop; i++) {
		swap(&seq[start], &seq[i]);
		pos = permute(perms, pos, seq+1, i);
		swap(&seq[start], &seq[i]);
	}
	return pos;
}
void resetMemory(int* mems[5], int* input, int len) {
	for(int i = 0; i < 5; i++) {
		memcpy(mems[i], input, len);
	}
}

void runCalcForAll(int* input, int len, FILE* file) {
	readInput(file, input);
	int prev = 0;
	int* mems[5];
	for (int i = 0; i < 5; i++) {
		mems[i] = malloc(len * sizeof(int));
	}

	int (*permuations)[5] = malloc(120 * 5 * sizeof(int));	
	int ints[5] = {0,1,2,3,4};
	permute(permuations, 0, ints, 0);		

	int max = 0;
	for(int i = 0; i < 120; i++) {
		int prev = 0;
		resetMemory(mems, input, len * sizeof(int));
		for( int j = 0; j < 5; j++) {
			prev = runCalc(input, len, permuations[i][j], prev);
		}
		if( prev > max) {
			max = prev;
		}
	}
	printf("MAX: %d", max);
}

int main() {
	FILE* file;
	file = fopen("inputday7.txt", "r");
	int length = countInts(file);
	if (length == -1) {
		return -1;
	}
	int* input = calloc(length,sizeof(int));
	runCalcForAll(input, length, file);

	printf("End of program");
	return 0;
}
