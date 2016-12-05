#include <stdio.h>
#include <stdlib.h>

void forward() { /*Your code here!*/ }
void right() { /*Your code here!*/ }
void left() { /*Your code here!*/ }
void back() { /*Your code here!*/ }


int main()
{
	while(1)
	{
		int i = -1;
		// This shows up on the screen
		printf("Please input a command (0 = forward, 1 = right, 2 = left, 3 = back, 4 = quit):");
		// Since the printf didn't end with a newline character (\n), we have to flush the IO buffer
		fflush(stdout);
		// Read user input, and save it to i
		scanf(" %d",&i);
		// Do something based on that input
		if(i==0) forward(); // Input was 0, go forward
		else if(i==1) right(); // Input was 1, go right
		else if(i==2) left(); // Input was 2, go left
		else if(i==3) back(); // Input was 3, go back
		else if(i==4) break; // Input was 4, quit
		else printf("Invalid input!\n"); // Input was something else
		// Because that printf ends with a newline, we don't need to use flush()
	}




	return 0;
}
