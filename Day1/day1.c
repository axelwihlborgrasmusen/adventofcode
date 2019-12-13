#include <stdio.h>
int main() {
	FILE* file;
	file = fopen("inputday1.txt", "r");
	int currentModule = 0;
	int sum = 0;
	int extraFuel = 0;
	int moduleFuel = 0;
	if (file) {
		fscanf (file, "%d", &currentModule);
		while (!feof(file)) {
			moduleFuel = (currentModule/3) - 2;
			extraFuel = moduleFuel;			
			while((extraFuel = (extraFuel/3) - 2) > 0) {
				moduleFuel += extraFuel;	
			}	

			sum += moduleFuel;
			fscanf (file, "%d", &currentModule);
		}
		fclose(file);
	}   


	printf("Sum is:  %d", sum);
	return 0;
}
