// *****************************
// t4_sensor1.c
// ECE 4723 Lab 4 Team 2
// Matthew Ashmore, Seth Barger, Huston Rogers, Corey Sherman
// *****************************
#include    "esos.h"
#include    "esos_pic24.h"
#include    "esos_pic24_rs232.h"
#include    "esos_pic24_sensor.h"
#include    "esos_sensor.h"

# include "esos_f14ui.c"
# include "revF14.h"

static uint16_t u16_thermometerValue;
static BOOL output_sw2 = FALSE;

//task to read potentiometer
ESOS_USER_TASK (READ_POT){
  ESOS_TASK_BEGIN();
  while(TRUE){
    ESOS_TASK_WAIT_SENSOR_QUICK_READ(u16_thermometerValue);
    ESOS_TASK_WAIT_TICKS(100);
  }
  ESOS_TASK_END();
}

// outputs to the serial port the potentiometer reading upon pressing SW1
ESOS_USER_TASK (SW1_DISPLAY) {
  ESOS_TASK_BEGIN();
  while(TRUE){
    ESOS_TASK_WAIT_UNTIL_UIF14_SW1_PRESSED();
    char output [] = "\nPotentiometer Reading: ";
    ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
    ESOS_TASK_WAIT_ON_SEND_STRING(output);
    ESOS_TASK_WAIT_ON_SEND_UINT32_AS_HEX_STRING((u16_thermometerValue << 16) + 0);
    ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
    ESOS_TASK_WAIT_UNTIL_UIF14_SW1_RELEASED();
    ESOS_TASK_YIELD();
  }
  ESOS_TASK_END();
}

// outputs to the serial port the potentiometer reading once per second after pressing SW2
ESOS_USER_TASK (SW2_DISPLAY) {
  ESOS_TASK_BEGIN();
  while(TRUE){
    ESOS_TASK_WAIT_UNTIL_UIF14_SW2_PRESSED();
    ESOS_TASK_WAIT_UNTIL_UIF14_SW2_RELEASED();
    output_sw2 = TRUE;
    ESOS_TASK_WAIT_UNTIL(esos_uiF14_isSW1Pressed() || esos_uiF14_isSW2Pressed());
    output_sw2 = FALSE;
    ESOS_TASK_WAIT_UNTIL(esos_uiF14_isSW1Released() && esos_uiF14_isSW2Released());
  }
  ESOS_TASK_END();
}

// outputs to console the potentiometer if in the correct state
ESOS_USER_TASK(OUTPUT_SW2_SECOND)
{
	ESOS_TASK_BEGIN();
  while(TRUE) {
    if(output_sw2){
      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      char output [] = "\nPotentiometer Reading: ";
      ESOS_TASK_WAIT_ON_SEND_STRING(output);
      ESOS_TASK_WAIT_ON_SEND_UINT32_AS_HEX_STRING((u16_thermometerValue << 16) + 0);
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_TICKS(1000);
    }
    ESOS_TASK_YIELD();
  }
	ESOS_TASK_END();
}

// user init must be called once
void user_init(void) {
  __esos_unsafe_PutString( HELLO_MSG );
  DELAY_US(10000);

  // configure our hardware and UI as needed by the tasks
  CONFIG_LED3();
  CONFIG_SW1();
  CONFIG_SW2();
  CONFIG_POT();

  config_esos_uiF14();
  esos_sensor_config_hw(POT_ADC_CHANNEL, 0); // configures ADC for potentiometer readings

  esos_uiF14_flashLED3(250); // heartbeat LED

  esos_RegisterTask(READ_POT);
  esos_RegisterTask(SW1_DISPLAY);
  esos_RegisterTask(SW2_DISPLAY);
  esos_RegisterTask(OUTPUT_SW2_SECOND);
} // end user_init()