// *****************************
// app_2_2_2.c
// *****************************
// ESOS application program to flash an LED on RB15.  Flashing LED is generated
// by a *user task*.


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
 * An ESOS task to manage the states of N/S and E/W stoplights.
 */
ESOS_USER_TASK(traffic_signal) {
  ESOS_TASK_BEGIN();
  while (TRUE) {
    //first stage
    red_ns = 1;
    amber_ns = 0;
    green_ns = 0;
    red_ew = 0;
    amber_ew = 0;
    green_ew = 1;
    ESOS_TASK_WAIT_TICKS(10000); // wait 10 seconds
    
    //second stage
    red_ns = 1;
    amber_ns = 0;
    green_ns = 0;
    red_ew = 0;
    amber_ew = 1;
    green_ew = 0;
    ESOS_TASK_WAIT_TICKS(3000); // wait 3 seconds

    //third stage
    red_ns = 0;
    amber_ns = 0;
    green_ns = 1;
    red_ew = 1;
    amber_ew = 0;
    green_ew = 0;
    ESOS_TASK_WAIT_TICKS(10000); // wait 10 seconds

    //fourth stage
    red_ns = 0;
    amber_ns = 1;
    green_ns = 0;
    red_ew = 1;
    amber_ew = 0;
    green_ew = 0;
    ESOS_TASK_WAIT_TICKS(3000); // wait 3 seconds
  } // endof while(TRUE)
  ESOS_TASK_END();
}

/*
 * An ESOS task to determine which stop light direction to display.
 */
ESOS_USER_TASK(direction) {
  ESOS_TASK_BEGIN();
  while (TRUE) {
    // if Switch 3 is depressed show E/W traffic status
    if (SW3 == 0)
    {
      LED1 = red_ew;
      LED2 = amber_ew;
      LED3 = !green_ew; // green led is inverted
    }
    // if Switch 3 is not depressed show N/S traffic status
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
