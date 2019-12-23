#include <stdio.h>
#include <stdlib.h>


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

int runCalc(int* input, int len) {
	int position = 0;
	int op;
	int firstValue;
	int secondValue;
	int storeAt;
	int mode1;
	int mode2;
	int mode3;

	//input[1] = noun;
	//input[2] = verb;

	 while ( (position - 2) < len)  {
	
		op = input[position];
		mode3 = op / 10000;
		mode2 = (op / 1000) % 10;
		mode1 = (op / 100) % 10;
		op = op % 100;		
		printf("OP: %d \n", op);
		switch(op) {
			case 1:
				firstValue = mode2 > 0 ? input[position + 1] : input[input[position + 1]];
				secondValue = mode1 > 0 ? input[position + 2] : input[input[position + 2]];
				input[input[position + 3]] = firstValue + secondValue;
				position += 4;
				break;
			case 2:		
				firstValue = mode2 > 0 ? input[position + 1] : input[input[position + 1]];
                                secondValue = mode1 > 0 ? input[position + 2] : input[input[position + 2]];
                                input[input[position + 3]] = firstValue * secondValue;
				position += 4;
				break;
			case 3:
				printf("Insert input: \n");
				scanf("%d", &(input[input[position + 1]]));
				position += 2;
				break;
			case 4:
				printf("%d \n", input[input[position + 1]]);
				position += 2;
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

void runCalcForAll(int* input, int len, FILE* file) {
	//for(int i = 0; i < 100; i++) {
	//	for(int j = 0; j<100; j++) {
			readInput(file, input);
	//		if (runCalc(input, len, i, j) == 19690720) {
	//			printf("The noun is: %d, the verb is %d, the answer is: %d", i, j, 100*i+j);
	//		}
	//	}
	//}
	int i = runCalc(input, len);
}

int main() {
	FILE* file;
	file = fopen("inputday52.txt", "r");
	int length = countInts(file);
	if (length == -1) {
		return -1;
	}
	int* input = calloc(length,sizeof(int));
	runCalcForAll(input, length, file);

	printf("End of program");
	return 0;
}
