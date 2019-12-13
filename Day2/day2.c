#include <stdio.h>


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

void runCalcForAll(int* input, int len, FILE* file) {
	for(int i = 0; i < 100; i++) {
		for(int j = 0; j<100; j++) {
			readInput(file, input);
			if (runCalc(input, len, i, j) == 19690720) {
				printf("The noun is: %d, the verb is %d, the answer is: %d", i, j, 100*i+j);
			}
		}
	}
}

int runCalc(int* input, int len, int noun, int verb) {
	int position = 0;
	int op;
	int firstValue;
	int secondValue;
	int storeAt;
	
	
	input[1] = noun;
	input[2] = verb;

	 while ( (position + 4) < len)  {

		op = input[position];
		firstValue = input[input[position + 1]];
		secondValue = input[input[position + 2]];
		storeAt = input[position + 3];		
		
		switch(op) {
			case 1:
				input[storeAt] = firstValue + secondValue;
				break;
			case 2:		
				input[storeAt] = firstValue * secondValue;
				break;
			case 99:
				return input[0];
		}
		position += 4;
	}
	return input[0];
}

int main() {
	FILE* file;
	file = fopen("inputday2.txt", "r");
	int length = countInts(file);
	if (length == -1) {
		return -1;
	}	

	int* input = calloc(length,sizeof(int));
	runCalcForAll(input, length, file);


	printf("End of program");
	return 0;
}
