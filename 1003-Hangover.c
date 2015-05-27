#include <stdio.h>
#include <stdlib.h>

float getReciprocal(int index){
	if(!index) return ;
	float result;
	result = (float)1/(float)index;
	return result;
}

int main(int argc, char *argv[]) {

	
	float target = 0.0;
	printf("Please input a float number: \n");
	scanf("%f", &target);
	int count = 1;
	while(target > 0){
		count++;
		target -= getReciprocal(count);
	}
	printf("count: %d\n", count - 1);
	
	return 0;
}
