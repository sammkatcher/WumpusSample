#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ev3_output.h"
#include "ev3_command.h"
#include "ev3_button.h"
#include "ev3_timer.h"
#include "ev3_lcd.h"
#include "movement.c"
#include "logic.c"


// Variables
struct square_struct {
	bool isUnknown;
	bool isSafe;
	bool isWumpus;
	bool isPit;
	bool isGold;
	bool mightBeWumpus;
	bool mightBePit;
	bool mightBeGold;

} square_default = {true, false, false, false, false, false, false, false, false};

typedef struct square_struct square;
// if i only think that 1 tile might be it, then it must be it
// for gold and wumpus only

typedef struct point_struct { int x,y; } point;



/*bool IsSafe(int x, int y) {
	// Pointer to square at x,y in grid
	square *s = &grid[x][y];
	// return true if it is not a Wumpus, Pit
	return !(s->isWumpus || s->isPit);
}
*/

int main(){

	#ifdef ROBOT_CONNECTED
    OutputInit();
    #endif
    /*int unsolved = 1;
    int input = 0;*/
    #define BOARDSIZE 4

	//2D Grid of spaces from 0 to 3
	square grid [4][4];
	
	//Set up the path
	#define PATH_SIZE 1000
	point path[PATH_SIZE];
	//Set the first point in the path to be 0,0
	point currentSquare = {0,0};
	path[0] = currentSquare;

	//create m and n as counters
	int m,n;
	for(m=0;m<BOARDSIZE;m++) // iterate over the y axis
	{
		// for each pointer
		for(n=0;n<BOARDSIZE;n++) // iterate over the x axis
		{
			grid[m][n] = square_default;
			printf("(Grid initialized)\n", );
		}
	}
	//Starting space is safe
	grid[0][0].isSafe = true;
	grid[0][0].visited = true;
	
	return 0;

	int instruction = 0;
	while(instruction == 0)
	{
		printf("Please input the number 1 to continue\n");
		scanf(" %d",&instruction);	
		//these if statements just make sure that the user actually inputs the value that we wanted
		//since we asked for a 1, then we allow "instruction" to remain as a 1, which will exit the
		//while loop
		if(instruction == 1)
		{
			instruction = 1;
		}//if, however, they do not type in a 1, then we set instruction to 0, which will make the loop repeat
		else
		{
			instruction = 0;
		}
	}


    while(unsolved)
    {
        printf("Input: ");
        fflush(stdout);
        scanf(" %d", &input);
        
        // Exit condition
        if(input > 16)
        {
            printf("Terminating.\n");
            fflush(stdout);
            break;
        }
        // extract information from the input here 


        #ifdef ROBOT_CONNECTED

        #endif
    }

    #ifdef ROBOT_CONNECTED
    OutputExit();
    #endif
    return 0;
}