#include "movement.c"

*int main()
{
    #ifdef ROBOT_CONNECTED
    OutputInit();
    #endif
    int unsolved = 1;
    int input = 0;
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

        #ifdef ROBOT_CONNECTED
        simple_forward();
        simple_turn_right();
        simple_turn_left();
        print_sensor();
        if (input == 1)
           sensor_forward();
        if (input == 2)
            sensor_backward();
        if (input == 3)
            turn_right();
        if (input ==4)
            turn_left();
        #endif
    }

    #ifdef ROBOT_CONNECTED
    OutputExit();
    #endif
    return 0;
}