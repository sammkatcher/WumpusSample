#include <stdio.h>
#include <stdlib.h>
#include "ev3_output.h"
#include "ev3_command.h"
#include "ev3_button.h"
#include "ev3_timer.h"
#include "ev3_lcd.h"





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

int main()
{//set up the main function
	//This is necessary at the beginning of main in order to prevent the
	//robot from doing really dumb stuff. It initializes motor values and
	//things like that so you can successfully start them
	OutputInit();
	
	//then call the forward function
	forward();
	//This takes care of all the shut down stuff for the motors. It has to be
	//at the end of main. 
	OutputExit();

	//then return from main
	return 0;
}