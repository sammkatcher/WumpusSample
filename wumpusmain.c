#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ev3_output.h"
#include "ev3_command.h"
#include "ev3_button.h"
#include "ev3_timer.h"
#include "ev3_lcd.h"
#include "movement.c"


// Variables
struct square_struct {
	bool isUnknown;
	bool isWumpus;
	bool isPit;
	bool isGold;
	bool mightBeWumpus;
	bool mightBePit;
	bool mightBeGold;

} square_default = {true, false, false, false, false, false, false};

typedef struct square_struct square;
// if i only think that 1 tile might be it, then it must be it
// for gold and wumpus only

typedef struct point_struct { int x,y; } point;

#define PATH_SIZE 1000
point path[PATH_SIZE];


/*bool IsSafe(int x, int y) {
	// Pointer to square at x,y in grid
	square *s = &grid[x][y];
	// return true if it is not a Wumpus, Pit
	return !(s->isWumpus || s->isPit);
}
*/

void UpdateBoard(){
	// given an input
	// given as a number that is a sum of the possible inputs
	// gold = 8, glimmer = 4, stench = 2, breeze = 1, nothing = 0
	// code does not keep track of the orientation of the robot
	// if the add is greater than 8, you're on the gold. cannot take more user input. must go back to start.
}

int main(){
	//we need to initialize main
	//This is necessary at the beginning of main in order to prevent the
	//robot from doing really dumb stuff. It initializes motor values and
	//things like that so you can successfully start them
	
	#ifdef ROBOT_CONNECTED
    OutputInit();
    #endif
    /*int unsolved = 1;
    int input = 0;*/
    #define BOARDSIZE 4

	//2D Grid of spaces from 0 to 3
	square grid [4][4];

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

	// Sample grid
	#ifndef ROBOT_CONNECTED
	char testgrid [4][4];
	testgrid[0][0] = 's';
	testgrid[0][1] = 's';
	testgrid[0][2] = 's';
	testgrid[0][3] = 'w';
	testgrid[1][0] = 's';
	testgrid[1][1] = 's';
	testgrid[1][2] = 'p';
	testgrid[1][3] = 's';
	testgrid[2][0] = 's';
	testgrid[2][1] = 's';
	testgrid[2][2] = 's';
	testgrid[2][3] = 's';
	testgrid[3][0] = 's';
	testgrid[3][1] = 's';
	testgrid[3][2] = 'g';
	testgrid[3][3] = 'p';
	
	int senseNumber = getSenseNumber(char testgrid, int x, int y, int BOARDSIZE);

	#endif
	// Get information about the spaces around the one it's currently in (as a number)
	// Parse information about cur space to figure out what's up (glimmers, breeze, smell)
	// 
	// Move accordingly

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


        // Using a single ampersand does bitwise and to
        //   determine what the input is.
        if(input & 0x00000008) // Input is: on gold
            printf("Gold! ");
        if(input & 0x00000004) // Input is: near gold
            printf("Glimmer! ");
        if(input & 0x00000002) // Input is: near wumpus
            printf("Wumpus! ");
        if(input & 0x00000001) // Input is: near hole
        {
            printf("Breeze! ");
        }
        printf("\n");
        fflush(stdout);

        #ifdef ROBOT_CONNECTED
        //simple_forward();
        //simple_turn_right();
        //simple_turn_left();
        //print_sensor();
        //sensor_forward();
        //sensor_backward();
        //turn_right();
        //turn_left();
        #endif
    }

    #ifdef ROBOT_CONNECTED
    OutputExit();
    #endif
    return 0;
}