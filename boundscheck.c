#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// only works on a square board
bool isOutofBounds(int x, int y, int max){
	if(x <= 0 && x < max){
		printf("X in Bounds");
		if (y <= 0 && y < max){
			printf("Y in Bounds\n");
			return false;
		}
	}
	else{
		printf("Out of Bounds\n");
		return true;
	}
};


int main() {
	
	printf("Test Case 1: 0,0 (T) \n");
	isOutofBounds(0, 0, 4);

	printf("Test Case 1: 3,3 (T) \n");
	isOutofBounds(3, 3, 4);

	printf("Test Case: -3, 3, (F)\n");
	isOutofBounds(-3, 3, 4);

	fflush(stdout);

}