#define ROBOT_CONNECTED
#ifdef ROBOT_CONNECTED
#include "ev3_output.h"
#include "ev3_command.h"
#include "ev3_button.h"
#include "ev3_timer.h"
#include "ev3_lcd.h"
#include "serial_read.h"
#endif


/********************************************
**  MODIFIED PROVIDED CODE                 **
**  These are the values you will change.  **
**                                         **
********************************************/

/* Change OUT_A, OUT_D, OUT_AD to match
 *   the actual setup of your robot
 * These values reflect the port names 
 */
#define LEFT_MOTOR OUT_D
#define RIGHT_MOTOR OUT_A
#define BOTH_MOTORS OUT_AD

/* Change 1 and 4 to match
 *   the actual setup of your robot
 * These values reflect the port numbers 
 */
#define LEFT_SENSOR 3
#define RIGHT_SENSOR 1

/* These values will be positive or 
 *   negative depending on the design
 *   of your robot. Additionally, the
 *   value will have to be calibrated
 */
#define RIGHT_MOTOR_FORWARD 40
#define RIGHT_MOTOR_BACKWARD -40
#define LEFT_MOTOR_FORWARD 40
#define LEFT_MOTOR_BACKWARD -40

/* These value affect the distance travelled
 *   when only moving forward or backward.
 *   Specifically, it affects simple_forward(),
 *   simple_backward(), as well as the movement
 *   into the square after aligning to the line
 *   with sensor_forward() and sensor_backward()
 */
#define FORWARD_WAIT 2500
#define BACKWARD_WAIT 1600

/* These are wait times; longer wait times
 *   mean that turns will be longer. This
 *   is only used in simple_right() and
 *   simple_left()
 */
#define TURN_RIGHT_WAIT 1500
#define TURN_LEFT_WAIT 1400

/* These values are stopping thresholds for
 *   turning in each direction. Higher numbers
 *   mean that the robot turns more
 */
#define TURN_RIGHT_DIST 350
#define TURN_LEFT_DIST 360

/* This value will have to be adjusted
 *   according to the setup of your robot
 *   and the lighting conditions of the 
 *   room
 */
#define SENSOR_THRESHHOLD 20
#define SENSOR_BITMASK 0x000000FF


/******************************************
**  UNMODIFIED PROVIDED CODE             **
**  Change this stuff at your own risk.  **
**                                       **
******************************************/

void simple_forward()
{
    SetPower(RIGHT_MOTOR, RIGHT_MOTOR_FORWARD);
    SetPower(LEFT_MOTOR, LEFT_MOTOR_FORWARD);
    On(OUT_ALL);
    Wait(FORWARD_WAIT);
    Off(OUT_ALL);
}

void simple_backward()
{
    SetPower(RIGHT_MOTOR, RIGHT_MOTOR_BACKWARD);
    SetPower(LEFT_MOTOR, LEFT_MOTOR_BACKWARD);
    On(OUT_ALL);
    Wait(BACKWARD_WAIT);
    Off(OUT_ALL);
}

void simple_turn_right()
{
    SetPower(RIGHT_MOTOR, RIGHT_MOTOR_BACKWARD);
    SetPower(LEFT_MOTOR, LEFT_MOTOR_FORWARD);
    On(OUT_ALL);
    Wait(TURN_RIGHT_WAIT);
    Off(OUT_ALL);
}

void simple_turn_left()
{
    SetPower(RIGHT_MOTOR, RIGHT_MOTOR_FORWARD);
    SetPower(LEFT_MOTOR, LEFT_MOTOR_BACKWARD);
    On(OUT_ALL);
    Wait(TURN_LEFT_WAIT);
    Off(OUT_ALL);
}

void print_sensor()
{
    int i = 0;
    int temp, sensor;
    while(i < 3000)
    {
        if(i % 50 == 0)
        {
            temp = ReadSerial(RIGHT_SENSOR);
            sensor = temp & 0x000000FF;
            printf("Sensor value: %d\n", sensor);
        }
        i += 1;
    }
}

void sensor_forward()
{
    int temporary_sensor_value = 0;
    int right_sensor_value = 0, left_sensor_value = 0;
    SetPower(RIGHT_MOTOR, RIGHT_MOTOR_FORWARD);
    SetPower(LEFT_MOTOR, LEFT_MOTOR_FORWARD);
    On(OUT_ALL);
    // First, move forward while both sensors are on black
    //   then stop when one sensor is over the white line
    do
    {
        temporary_sensor_value = ReadSerial(RIGHT_SENSOR);
        right_sensor_value = temporary_sensor_value & 0x000000FF;
        temporary_sensor_value = ReadSerial(LEFT_SENSOR);
        left_sensor_value = temporary_sensor_value & 0x000000FF;
    } while((right_sensor_value < SENSOR_THRESHHOLD) && 
            (left_sensor_value < SENSOR_THRESHHOLD));
    Off(OUT_ALL);
    // Next, we want to adjust based on which is on the line

    // If both sensors are on the line, just go forward
    if((left_sensor_value >= SENSOR_THRESHHOLD) && 
        (right_sensor_value >= SENSOR_THRESHHOLD))
    {
        simple_forward();
        return;
    }
    // If the left sensor is on the line, we only want the right
    //    motor to move until the right sensor is on the line
    if(left_sensor_value >= SENSOR_THRESHHOLD)
    {
        On(RIGHT_MOTOR);
        do
        {
            temporary_sensor_value = ReadSerial(RIGHT_SENSOR);
            right_sensor_value = temporary_sensor_value & 0x000000FF;
        } while(right_sensor_value < SENSOR_THRESHHOLD);
        Off(RIGHT_MOTOR);
        simple_forward();
        return;
    }
    if(right_sensor_value >= SENSOR_THRESHHOLD)
    {
        On(LEFT_MOTOR);
        do
        {
            temporary_sensor_value = ReadSerial(LEFT_SENSOR);
            left_sensor_value = temporary_sensor_value & 0x000000FF;
        } while(left_sensor_value < SENSOR_THRESHHOLD);
        Off(LEFT_MOTOR);
        simple_forward();
        return;
    }
}

void sensor_backward()
{
    int temporary_sensor_value = 0;
    int right_sensor_value = 0, left_sensor_value = 0;
    SetPower(RIGHT_MOTOR, RIGHT_MOTOR_BACKWARD);
    SetPower(LEFT_MOTOR, LEFT_MOTOR_BACKWARD);
    On(OUT_ALL);
    // First, move forward while both sensors are on black
    //   then stop when one sensor is over the white line
    do
    {
        temporary_sensor_value = ReadSerial(RIGHT_SENSOR);
        right_sensor_value = temporary_sensor_value & 0x000000FF;
        temporary_sensor_value = ReadSerial(LEFT_SENSOR);
        left_sensor_value = temporary_sensor_value & 0x000000FF;
    } while((right_sensor_value < SENSOR_THRESHHOLD) && 
            (left_sensor_value < SENSOR_THRESHHOLD));
    Off(OUT_ALL);

    // Next, we want to adjust based on which is on the line

    // If both sensors are on the line, just go forward
    if((left_sensor_value >= SENSOR_THRESHHOLD) && 
        (right_sensor_value >= SENSOR_THRESHHOLD))
    {
        simple_backward();
        return;
    }
    // If the left sensor is on the line, we only want the right
    //    motor to move until the right sensor is on the line
    if(left_sensor_value >= SENSOR_THRESHHOLD)
    {
        On(RIGHT_MOTOR);
        do
        {
            temporary_sensor_value = ReadSerial(RIGHT_SENSOR);
            right_sensor_value = temporary_sensor_value & 0x000000FF;
        } while(right_sensor_value < SENSOR_THRESHHOLD);
        Off(RIGHT_MOTOR);
        simple_backward();
        return;
    }
    if(right_sensor_value >= SENSOR_THRESHHOLD)
    {
        On(LEFT_MOTOR);
        do
        {
            temporary_sensor_value = ReadSerial(LEFT_SENSOR);
            left_sensor_value = temporary_sensor_value & 0x000000FF;
        } while(left_sensor_value < SENSOR_THRESHHOLD);
        Off(LEFT_MOTOR);
        simple_backward();
        return;
    }

}

void turn_right()
{
    ResetAllTachoCounts(BOTH_MOTORS);
    // To turn right, we set the left motor forward
    //   and the right motor backward
    SetPower(RIGHT_MOTOR, RIGHT_MOTOR_BACKWARD);
    SetPower(LEFT_MOTOR, LEFT_MOTOR_FORWARD);
    On(OUT_ALL);
    // We'll use the left motor for reference
    // If forward on the left motor is positive, then
    //   we want to continue until it is greater than a
    //   large positive number
    if(LEFT_MOTOR_FORWARD > 0)
    {
        while(MotorRotationCount(LEFT_MOTOR) < TURN_RIGHT_DIST){ }
    }
    else // If forward on the left motor is negative,
    {    //   then we want to continue until it's less 
         //   than a large negative number
        while(MotorRotationCount(LEFT_MOTOR) > (-1)*TURN_RIGHT_DIST){ }
    }
    Off(OUT_ALL);
}

void turn_left()
{
    ResetAllTachoCounts(BOTH_MOTORS);
    // To turn left, we set the right motor forward
    //   and the left motor backward
    SetPower(RIGHT_MOTOR, RIGHT_MOTOR_FORWARD);
    SetPower(LEFT_MOTOR, LEFT_MOTOR_BACKWARD);
    On(OUT_ALL);
    // We'll use the right motor for reference
    // If forward on the right motor is positive, then
    //   we want to continue until it is greater than a
    //   large positive number
    if(RIGHT_MOTOR_FORWARD > 0)
    {
        while(MotorRotationCount(RIGHT_MOTOR) < TURN_LEFT_DIST){ }
    }
    else // If forward on the right motor is negative,
    {    //   then we want to continue until it's less 
         //   than a large negative number
        while(MotorRotationCount(RIGHT_MOTOR) > (-1)*TURN_LEFT_DIST){ }
    }
    Off(OUT_ALL);
}


