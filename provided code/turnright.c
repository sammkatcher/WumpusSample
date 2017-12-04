#include <stdio.h>
#include <stdlib.h>
#include "ev3_output.h"
#include "ev3_command.h"
#include "ev3_button.h"
#include "ev3_timer.h"
#include "ev3_lcd.h"



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
	while(MotorRotationCount(OUT_D)>-191){ }
	//then we turn all the motors off
	Off(OUT_ALL);
}


int main()
{//set up the main function

	//This is necessary at the beginning of main in order to prevent the
	//robot from doing really dumb stuff. It initializes motor values and
	//things like that so you can successfully start them
	OutputInit();
	
	//then call the turn right function
	turnright();
	
	//This takes care of all the shut down stuff for the motors. It has to be
	//at the end of main. 
	OutputExit();

	//return from main
	return 0;
}
