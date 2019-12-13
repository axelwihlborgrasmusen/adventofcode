#include <stdio.h>


void readInput(FILE* file, int* input) {
	char temp;
	char number[3];
	int count = 0;
	int inputs = 0; 
	while(fscanf(file, "%c", &temp) != EOF) {
		if(temp != ',') {
			number[0] = temp;
			count++;
		}else {
			count = 0;
			input[inputs] = atoi(number);
			input++;
		}
	}
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
	return count;  

}

int main() {
	FILE* file;
	file = fopen("inputday2.txt", "r");
	int length = countInts(file);
	if (length == -1) {
		return -1;
	}	
	printf("Len is:  %d", length);

	int* input = calloc(length,sizeof(int));
	readInput(file, input);

	for (int i = 0; i<length; i++) {
		printf("input got: %d", input[i]);
}
	printf("Sum is:  %d", length);
	return 0;
}
