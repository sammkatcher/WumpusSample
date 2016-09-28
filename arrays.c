#include <stdio.h>
#include <stdlib.h>

//This allows for the array size to be changed easily w/o
//extensive code modification
#define BOARDSIZE 4

int main()
{
	//create a 2d array of chars or size 4x4
	char array[BOARDSIZE][BOARDSIZE];
	//create m and n as counters
	int m,n;
	for(m=0;m<BOARDSIZE;m++) // iterate over the y axis
	{
		for(n=0;n<BOARDSIZE;n++) // iterate over the x axis
		{
			// allocate memory for the array
			array[m][n] = (char*)malloc( sizeof( char) );
			// assign the value at that position
			array[m][n] = '_';
			// if the m and n are equal, set as a * (diagonal from top left)
			if(m==n) array[m][n] = '*';
			// diagonal from top right
			if(m+n == BOARDSIZE - 1) array[m][n] = '*';
			// print all the chars in the array
			printf("%c",array[m][n]);
		}
		// newline after each row
		printf("\n");
	}
	
	return 0;
}
