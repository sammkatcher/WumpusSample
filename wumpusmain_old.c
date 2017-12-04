#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ev3_output.h"
#include "ev3_command.h"
#include "ev3_button.h"
#include "ev3_timer.h"
#include "ev3_lcd.h"

//#include "remote.c"

//Citation for left() and right() and MoveForward(): https://agentesinteligentesp2014.wordpress.com/2014/04/29/wumpus-con-lego/

/*********************************************************
 * BEGIN PROVIDED CODE
 *********************************************************/
void turnleft(){
	//before doing anything we reset the tachometers, that way
	//we can measure the turn for consistency
	ResetAllTachoCounts(OUT_AD);

	//we set the motors to move in opposite directions, at the same speed
	SetPower(OUT_A, -40);
	SetPower(OUT_D, 40);
	//then turn the motors on. This should robot rotate in place
	On(OUT_ALL);
	
	//We track the rotation of motor A, and continue to rotate until the
	//tachometer's count is -380
	//the rotation count starts at 0 because of the tacho counter reset
	//and decreases because the motor's rotation is in the negative direction
	//when it gets lower than -380, we turn the motors off
	while(MotorRotationCount(OUT_A)>-380)
	{
		//We don't do anything here, we simply look at the tacho and decide
		//whether to continue the loop or break out and turn the motor off
	}

	//then we turn all the motors off
	Off(OUT_ALL);

}

void turnright()
{
	//before doing anything we reset the tachometers, that way
	//we can measure the turn for consistency
	ResetAllTachoCounts(OUT_AD);

	//for turning right, we set motor A to move forward at speed 40
	//and motor D to move backwards at speed 40
	SetPower(OUT_A, 40);
	SetPower(OUT_D, -40);
	//then we turn the motors on
	On(OUT_ALL);

	//We track the rotation of motor D, and continue to rotate until the
	//tachometer's count is -191.
	//we don't do anything while this is looping
	//because OUT_D is negative and we reset the tachometer,
	//it will start at 0 and decrease. we continue the loop until
	//it decreases to a number lower than -191
	while(MotorRotationCount(OUT_D)>-395){ }
	//then we turn all the motors off
	Off(OUT_ALL);
}

void forward_serial_read()
{
	//We set the "threshold" value for determining what color we're looking at
	//to 20, but this number may be different for you.
	int THRESHOLD = 20;
	
	//"sensor" is where we'll store the value that is returned by the sensor on out bot
	int sensor = 0;
	
	//before we can use the input, we have to make some changes to it, so we use a temporary variable
	int temp = 0;
	
	//We set the power level for the motors before moving forward until a line
	SetPower(OUT_A, 40);
	SetPower(OUT_D, 40);

	//Then we turn the motors on
	On(OUT_ALL);
	
	while(sensor < THRESHOLD)
	{
		//we will continue to execute the code in this block while the sensor
		//is picking up a value less than the threshold. This should mean that, while the robot is
		//over a black (or in general, dark) surface, it will continue to repeat these instructions
	
		//we read the value from serial port 1 into the temp variable
		temp = ReadSerial(1);

		//the serial read returns a 12-bit value, and the only part we care about is the last 8 bits, so we use a bitmask
		//to evaluate the input correctly. For more information about bitmasking, see the readme about it
		sensor = temp & 0x000000FF;
	
	}
	
	//Once we've finished moving, we turn the motors off and return
	Off(OUT_ALL);
	return;
	
}

void forward()
{
	//we set the power of motor A to 40
  SetPower(OUT_A, 40);
	//then we set the power of motor D to 40
  SetPower(OUT_D, 40);
	//then we turn all the motors on
  On(OUT_ALL);
	//we let it run for 2.750 seconds
	//since the Wait function takes its argument in milliseconds
  Wait(2750);
	//then we turn all the motors off (so the bot will stop moving
  Off(OUT_ALL);
}

/*******************************************************************
 * END PROVIDED CODE
 *******************************************************************/

// Variables
typedef struct square_struct {
	bool isUnknown;
	bool isWumpus;
	bool isPit;
	bool isGold;
} square;

typedef struct point_struct { int x,y; } point;

//2D Grid of spaces from 0 to 3
square grid [4][4];

#define PATH_SIZE 1000
point path[PATH_SIZE];

square CreateSquare() {
	square s;
	s.isUnknown = true;
	s.isWumpus = false;
	s.isPit = false;
	s.isGold = false;
	return s;
}

bool IsSafe(int x, int y) {
	// Pointer to square at x,y in grid
	square *s = &grid[x][y];
	// return true if it is not a Wumpus, Pit
	return !(s->isWumpus || s->isPit);
}


/*bool IfSafe(){
	// turn Unknown to false
}*/


// Move to goal square
int Move(point startingLocation, point endingLocation){
	//Only move onto free spaces or unknown spaces with no stench of Wampus or breeze of pit
	/*
	void MoveForward(int pos, int &i, int &j) {
		motor[motorB] = SPEED;
		motor[motorC] = SPEED;

		while(HTCS2readcolor(HTCS2) == black) { }
		wait1Msec(4000);
		motor[motorB] =0;
		motor[motorC] = 0;
		if(pos==1) {
		i++;
		}
		if(pos==4) {
		j++;
		}
		if(pos==3) {
		i–;
		}
		if(pos==2) {
		j–;
		}
	}
	*/

}

int Discover(){
	/*Check if can smell stench of Wampus, feel breeze of pit, see glimmer of gold.
	If a square is next to multiple items, the robot gets multiple clues 
	Being next to multiple pits does not ‘increase’ the breeze: the robot will simply feel a breeze. 
	When the Wumpus has been killed, the square becomes an empty square, and the smells in the adjacent squares go away
	
	
	
*/}


int main(){
	//we need to initialize main
	//This is necessary at the beginning of main in order to prevent the
	//robot from doing really dumb stuff. It initializes motor values and
	//things like that so you can successfully start them
	OutputInit();

	//call the turn left function
	//turnleft();
	//turnright();



	int instruction = 0;
	while(instruction == 0)
	{
		//the function printf prints information to the terminal. It takes a variable number of
		//arguments, but how you should be using it for this project is like I have shown below.
		//You will only be passing printf 1 argument, which is a string of characters inside of 
		//quotation marks. The \n at the end of mine represents a newline character, which will
		//print a newline to the terminal, and is necessary in order to get the terminal to actually
		//print the string out
		printf("Please input the number 1 to continue\n");
		
		//scanf is how you receive information from the user at the terminal. In this particular case,
		//we use the " %d" to tell it that we want to take in an integer from the user. the second
		//argument tells scanf where to store this information. Because we are scanning in an integer,
		//we have to pass scanf a reference to the variable, which is why there is an ampersand in front
		//of "instruction". 
		//It is possible that you will not need the space in front of the %d, however I remember distinctly
		//having problems with giving the program input, and this fixed it. It had something to do with
		//sending a newline repeatedly, and this solved that issue. If for some reason you have problems with
		//this, you might try removing the space, but it shouldn't cause you any issues.
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
	
	//then call the forward funct
	
	forward_serial_read();
	//This takes care of all the shut down stuff for the motors. It has to be
	//at the end of main. 
	OutputExit();

	//then return from main
	return 0;
}