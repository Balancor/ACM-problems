#include <stdio.h>
#include <stdlib.h>

float income[] = {
	100.00,
	489.12,
	12454.12,
	1234.10,
	823.05,
	109.20,
	5.27,
	1542.25,
	839.18,
	83.99,
	1295.01,
	1.75,
};

int main(int argc, char *argv[]) {
	int monthes = sizeof(income) / sizeof(float);
	
	int i=0;
	float average = 0.0;
	for(i = 0; i < monthes; i++){
		average += (float)income[i] / monthes;
	}
	
	printf("$%.2f\n", average);
	return 0;
}
