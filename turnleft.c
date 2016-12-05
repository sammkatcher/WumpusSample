#include <stdio.h>
#include <stdlib.h>
#include "ev3_output.h"
#include "ev3_command.h"
#include "ev3_button.h"
#include "ev3_timer.h"
#include "ev3_lcd.h"


void turnleft()
{
	//before doing anything we reset the tachometers, that way
	//we can measure the turn for consistency
	ResetAllTachoCounts(OUT_AD);

	//we set the motors to move in opposite directions, at the same speed
	SetPower(OUT_A, -40);
	SetPower(OUT_D, 40);
	//then turn the motors on. This should robot rotate in place
	On(OUT_ALL);
	
	//We track the rotation of motor A, and continue to rotate until the
	//tachometer's count is -187
	//the rotation count starts at 0 because of the tacho counter reset
	//and decreases because the motor's rotation is in the negative direction
	//when it gets lower than -187, we turn the motors off
	while(MotorRotationCount(OUT_A)>-187)
	{
		//We don't do anything here, we simply look at the tacho and decide
		//whether to continue the loop or break out and turn the motor off
	}

	//then we turn all the motors off
	Off(OUT_ALL);

}


int main()
{//we need to initialize main
	//This is necessary at the beginning of main in order to prevent the
	//robot from doing really dumb stuff. It initializes motor values and
	//things like that so you can successfully start them
	OutputInit();

	//call the turn left function
	turnleft();
	
	//This takes care of all the shut down stuff for the motors. It has to be
	//at the end of main. 
	OutputExit();

	//then return from main
	return 0;
}
