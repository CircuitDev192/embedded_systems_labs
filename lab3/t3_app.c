// *****************************
// t3_app.c
// ECE 4723 Lab 3 Team 2
// Matthew Ashmore, Seth Barger, Huston Rogers, Corey Sherman
// *****************************
#include    "esos.h"
#include    "esos_pic24.h"
#include    "esos_pic24_rs232.h"

# include "esos_f14ui.c"
# include "revF14.h"

// LED1 is illuminated when SW1/2 is pressed and LED1 flashes 3 times when SW1/2 are double-pressed
ESOS_USER_TASK(LED1_SW_TASK) {
  ESOS_TASK_BEGIN();
  while (TRUE) {
    if (esos_uiF14_isSW1DoublePressed() || esos_uiF14_isSW2DoublePressed())
    {
      esos_uiF14_flashLED1(300);
      ESOS_TASK_WAIT_TICKS(300*3);
    } else if (esos_uiF14_isSW1Pressed() || esos_uiF14_isSW2Pressed())
    {
      esos_uiF14_turnLED1On();
    } else {
      esos_uiF14_turnLED1Off();
    }
    ESOS_TASK_YIELD();
  } // endof while(TRUE)
  ESOS_TASK_END();
}

// Reads the RPG state and flashes LED2 accordingly
ESOS_USER_TASK (LED2_RPG_TASK) {
  ESOS_TASK_BEGIN();
  while(TRUE){
    if (esos_uiF14_isRPGTurningSlow()) {
      //slow
      esos_uiF14_turnLED2On();
    } else if (esos_uiF14_isRPGTurningMedium()) {
      //medium
      esos_uiF14_flashLED2(500);
    } else if (esos_uiF14_isRPGTurningFast()) {
      //fast
      esos_uiF14_flashLED2(100);
    } else if (!esos_uiF14_isRPGTurning()){
      //no movement
      esos_uiF14_turnLED2Off();
    }
    ESOS_TASK_YIELD();
  }
  ESOS_TASK_END();
}

// INPUT_UI_TASK provides the user a way to enter values for switch double press times and RPG threshholds.
ESOS_USER_TASK(INPUT_UI_TASK) {
  static uint8_t single_char;
  static uint8_t choice;
  static uint8_t many_char[20];
  static uint16_t u16_newVal = 0;
  static uint8_t index = 0;
  char str[] = "\nPick a value to change.\na - Switch 1 Double Press Period\nb - Switch 2 Double Press Period\nc - Switch 3 Double Press Period\nd - RPG Fast Threshold\ne - RPG Medium Threshold\nf - RPG Slow Threshold\n";
  char str2[] = "\nEnter a new value in milliseconds.\n";
  char str3[] = "\nBEEP BOP BOOP. Value was changed to ";
  char str4[] = "\nBEEP BOP BRRRRRRR. Invalid value!\n";

  ESOS_TASK_BEGIN();
  while (TRUE) {
    ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
    ESOS_TASK_WAIT_ON_SEND_STRING(str);
    ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

    // User Choice
    ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
    ESOS_TASK_WAIT_ON_GET_UINT8(single_char);
    ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();
    choice = single_char;
    ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
    ESOS_TASK_WAIT_ON_SEND_UINT8(choice);
    ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

    BOOL isOption = choice == 'a' || choice == 'b' || choice == 'c' || choice == 'd' || choice == 'e' || choice == 'f';
    
    // Numerical Input
    if (isOption)
    {
      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING(str2);
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

      // GET_CHARACTER_ARRAY (could be improved with separate task using semaphores)
      while (TRUE){
        ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
        ESOS_TASK_WAIT_ON_GET_UINT8( single_char );
        ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();
        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_UINT8( single_char );
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        if (single_char == 13) //CARRIAGE RETURN
        {
          // INTEGER PARSING
          u16_newVal = esos_uiF14_parseValue_i16(many_char, index);
          index = 0;
          uint8_t i = 0;
          i = 0;
          while ( i < 20 )
          {
            many_char[i] = NULL;
            i+=1;
          }
          break;
        } else if (single_char == 8) // BACKSPACE HANDLING
        {
          index -= 1;
          many_char[index] = 0;
        } else // LOG CHARACTER INTO ARRAY
        {
          many_char[index] = single_char;
          index += 1;
          if (index > 19)
          {
            index = 0;
          }
        }
      }

      // Minimum value of 50 milliseconds throws error
      if (u16_newVal <= 50){
        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_STRING(str4);
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        continue;
      }

      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING(str3);
      ESOS_TASK_WAIT_ON_SEND_UINT32_AS_HEX_STRING((u16_newVal << 16) + 0);
      ESOS_TASK_WAIT_ON_SEND_STRING(".\n");
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

      if(choice == 'a'){
        esos_uiF14_setSW1DoublePressPeriod(u16_newVal);
      } else if (choice == 'b') {
        esos_uiF14_setSW2DoublePressPeriod(u16_newVal);
      } else if (choice == 'c') {
        esos_uiF14_setSW3DoublePressPeriod(u16_newVal);
      } else if (choice == 'd') {
        esos_uiF14_setRPGTurningFast(u16_newVal);
      } else if (choice == 'e') {
        esos_uiF14_setRPGTurningMedium(u16_newVal);
      } else if (choice == 'f') {
        esos_uiF14_setRPGTurningSlow(u16_newVal);
      } else {
        //do nothing
      }
    }
    ESOS_TASK_YIELD();
  } // endof while(TRUE)
  ESOS_TASK_END();
}

// OUTPUT_TASK reads switches/RPG states and outputs to console
ESOS_USER_TASK(OUTPUT_TASK) {
  ESOS_TASK_BEGIN();
  while(TRUE) {
    if(!SW1){
      char psz_Output_SW1[] = "SW1 Pressed.\n";
      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING(psz_Output_SW1);
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_TICKS(__ESOS_UIF14_UI_PERIOD_MS);
    }else if(!SW2) {
      char psz_Output_SW2[] = "SW2 Pressed.\n";
      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING(psz_Output_SW2);
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_TICKS(__ESOS_UIF14_UI_PERIOD_MS);
    } else if(!SW3) {
      char psz_Output_SW3[] = "SW3 Pressed.\n";
      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING(psz_Output_SW3);
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_TICKS(__ESOS_UIF14_UI_PERIOD_MS);
    } else if(esos_uiF14_isRPGTurningSlow()) {
      char psz_Output_RPG_Slow[] = "RPG is turning Slowly.\n";
      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING(psz_Output_RPG_Slow);
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_TICKS(__ESOS_UIF14_UI_PERIOD_MS*25);
    } else if(esos_uiF14_isRPGTurningMedium()) {
      char psz_Output_RPG_Medium[] = "RPG is turning Medium.\n";
      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING(psz_Output_RPG_Medium);
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_TICKS(__ESOS_UIF14_UI_PERIOD_MS*25);
    } else if(esos_uiF14_isRPGTurningFast()) {
      char psz_Output_RPG_Fast[] = "RPG is turning Fast.\n";
      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING(psz_Output_RPG_Fast);
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_TICKS(__ESOS_UIF14_UI_PERIOD_MS*25);
    } 
     if(esos_uiF14_isSW1DoublePressed()) {
      char psz_Output_SW1_Double[] = "SW1 double pressed.\n";
      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING(psz_Output_SW1_Double);
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_TICKS(__ESOS_UIF14_UI_PERIOD_MS*25);
    } else if(esos_uiF14_isSW2DoublePressed()) {
      char psz_Output_SW2_Double[] = "SW2 double pressed.\n";
      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING(psz_Output_SW2_Double);
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_TICKS(__ESOS_UIF14_UI_PERIOD_MS*25);
    } else if(esos_uiF14_isSW3DoublePressed()) {
      char psz_Output_SW3_Double[] = "SW3 double pressed.\n";
      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING(psz_Output_SW3_Double);
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_TICKS(__ESOS_UIF14_UI_PERIOD_MS*25);
    }
    ESOS_TASK_YIELD();
  }
  ESOS_TASK_END();
}

/****************************************************
 *  user_init()
 ****************************************************
 */
void user_init(void) {
  __esos_unsafe_PutString( HELLO_MSG );

  // configure our hardware and UI as needed by the tasks
  CONFIG_LED1();
  CONFIG_LED2();
  CONFIG_LED3();
  CONFIG_SW1();
  CONFIG_SW2();
  CONFIG_SW3();
  CONFIG_RPG();
  config_esos_uiF14();

  esos_uiF14_flashLED3(500); // heartbeat LED

  esos_RegisterTask(LED2_RPG_TASK);
  esos_RegisterTask(LED1_SW_TASK);
  esos_RegisterTask(INPUT_UI_TASK);
  esos_RegisterTask(OUTPUT_TASK);

} // end user_init()