#include <stdio.h>
#include <math.h>


int main() {
	int start = 254032;
	int stop = 789860;
	int numbers[6];
	int success = 0;
	for(int i = start; i <= stop; i++) {
		int current = i;
		for(int t = 5; t > -1; t--) {
			numbers[t] = (current % 10);
			current /= 10;
		}
		
		int fail = 0;
		int found = 0;
		int foundInt = 0;
		for(int t = 0; t < 5; t++) {
			if(numbers[t] > numbers[t+1]) {
				fail = 1;
				i+=((numbers[t]-numbers[t+1]) * pow(10, 4-t)) - 1;
				break;	
			} else if (numbers[t] != foundInt && !found && numbers[t] == numbers[t+1]) {
				found = 1;
				foundInt = numbers[t];
			} else if (numbers[t+1] == foundInt) {
				found = 0;
			}
		}
		if(!fail && found) success++;


	}	

	printf("Success: %d", success);
	return 0;
}
