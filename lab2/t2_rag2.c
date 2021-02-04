// *****************************
// app_2_2_3.c
// *****************************
// ESOS application program to generate traffic signals with added rush-hour mode.


// INCLUDEs go here  (First include the main esos.h file)
//      After that, the user can include what they need
#include    "esos.h"
#include    "esos_pic24.h"
#include    "esos_pic24_rs232.h"

#include    "revF14.h"

// PROTOTYPEs go here

// GLOBALs go here
BOOL red_ns = 1;
BOOL amber_ns = 1;
BOOL green_ns = 1;
BOOL red_ew = 1;
BOOL amber_ew = 1;
BOOL green_ew = 1;

//  Generally, the user-created semaphores will be defined/allocated here


/************************************************************************
 * User supplied functions
 ************************************************************************
 */

/*
 * An ESOS task to manage the state of N/S/E/W stoplights.
 *
 */
ESOS_USER_TASK(traffic_signal) {
  ESOS_TASK_BEGIN();
  while(TRUE) {
    while (SW1) {    //SW1 denotes that the stoplight is in "Normal Operation"
      //first stage   N-S = red | E-W = green
      red_ns = 1;
      amber_ns = 0;
      green_ns = 0;
      red_ew = 0;
      amber_ew = 0;
      green_ew = 1;
      ESOS_TASK_WAIT_TICKS(10000); // wait 10 seconds
      
      //second stage  N-S = red | E-W = amber
      red_ns = 1;
      amber_ns = 0;
      green_ns = 0;
      red_ew = 0;
      amber_ew = 1;
      green_ew = 0;
      ESOS_TASK_WAIT_TICKS(3000); // wait 3 seconds

      //third stage   N-S = green | E-W = red
      red_ns = 0;
      amber_ns = 0;
      green_ns = 1;
      red_ew = 1;
      amber_ew = 0;
      green_ew = 0;
      ESOS_TASK_WAIT_TICKS(10000); // wait 10 seconds

      //fourth stage  N-S = amber | E-W = red
      red_ns = 0;
      amber_ns = 1;
      green_ns = 0;
      red_ew = 1;
      amber_ew = 0;
      green_ew = 0;
      ESOS_TASK_WAIT_TICKS(3000); // wait 3 seconds
      SW1=!SW1; //debounce switch
    } // endof while(!SW1)

    while(!SW1) {  // !SW1 denotes that the stoplight is in "Rush-Hour" operation

      //first stage   N-S = red | E-W = green
      red_ns = 1;
      amber_ns = 0;
      green_ns = 0;
      red_ew = 0;
      amber_ew = 0;
      green_ew = 1;
      ESOS_TASK_WAIT_TICKS(30000); // wait 30 seconds
      
      //second stage  N-S = red | E-W = amber
      red_ns = 1;
      amber_ns = 0;
      green_ns = 0;
      red_ew = 0;
      amber_ew = 1;
      green_ew = 0;
      ESOS_TASK_WAIT_TICKS(3000); // wait 3 seconds

      //third stage   N-S = red | E-W = red
      red_ns = 1;
      amber_ns = 0;
      green_ns = 0;
      red_ew = 1;
      amber_ew = 0;
      green_ew = 0;
      ESOS_TASK_WAIT_TICKS(1000); // wait 1 second

      //fourth stage  N-S = greed | E-W = red
      red_ns = 0;
      amber_ns = 0;
      green_ns = 1;
      red_ew = 1;
      amber_ew = 0;
      green_ew = 0;
      ESOS_TASK_WAIT_TICKS(30000); // wait 30 seconds

      //fifth stage   N-S = amber | E-W = red
      red_ns = 0;
      amber_ns = 1;
      green_ns = 0;
      red_ew = 1;
      amber_ew = 0;
      green_ew = 0;
      ESOS_TASK_WAIT_TICKS(3000); // wait 3 seconds

      //sixth stage   N-S = red | E-W = red
      red_ns = 1;
      amber_ns = 0;
      green_ns = 0;
      red_ew = 1;
      amber_ew = 0;
      green_ew = 0;
      ESOS_TASK_WAIT_TICKS(1000); // wait 1 second
      SW1=!SW1; //debounce switch
    } //end of while(!SW1)
  } //end of while true
  ESOS_TASK_END();
}

/*
 * An ESOS task to determine which stop light direction to display.
 *
 */
ESOS_USER_TASK(direction) {
  ESOS_TASK_BEGIN();
  while (TRUE) {
    // if Switch 3 is depressed display E-W stoplight
    if (SW3 == 0)
    {
      LED1 = red_ew;
      LED2 = amber_ew;
      LED3 = !green_ew; // green led is inverted
    }
    // if Switch 3 is not depressed display N-S stoplight
    else {
      LED1 = red_ns;
      LED2 = amber_ns;
      LED3 = !green_ns; // green led is inverted
    }
    ESOS_TASK_YIELD();
  } // endof while(TRUE)
  ESOS_TASK_END();
}

/****************************************************
 *  user_init()
 ****************************************************
 */
void user_init(void) {
  // Call the hardware-provided routines to print the
  // HELLO_MSG to the screen.  Must use this call because
  // the ESOS communications subsystems is not yet fully
  // initialized, since this call is in user_init()
  //
  // In general, users should call hardware-specific
  // function like this.
  __esos_unsafe_PutString( HELLO_MSG );

  // configure our hardware as needed by the tasks
  CONFIG_LED1();
  CONFIG_LED2();
  CONFIG_LED3();
  CONFIG_SW1();
  CONFIG_SW2();
  CONFIG_SW3();

  // user_init() should register at least one user task
  esos_RegisterTask(traffic_signal);
  esos_RegisterTask(direction);

} // end user_init()
