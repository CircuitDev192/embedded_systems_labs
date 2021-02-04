// *****************************
// t4_sensor2.c
// ECE 4723 Lab 4 Team 2
// Matthew Ashmore, Seth Barger, Huston Rogers, Corey Sherman
//
// uses the thermometer and allows the user to look at min/max values of thermometer
// *****************************
#include    "esos.h"
#include    "esos_pic24.h"
#include    "esos_pic24_rs232.h"
#include    "esos_pic24_sensor.h"
#include    "esos_sensor.h"

# include "esos_f14ui.c"
# include "revF14.h"

static uint16_t u16_thermometerValue;
static uint8_t mode;
static uint8_t samples;
static uint16_t temp_val_array[64];
static uint16_t output;
static BOOL output_sw2 = FALSE;

//task to read for sw1
ESOS_USER_TASK (SW1_READ_TEMP){
  ESOS_TASK_BEGIN();
  while(TRUE){
    ESOS_TASK_WAIT_UNTIL_UIF14_SW1_PRESSED();
    //whenever the button is pushed, grab the value
    ESOS_TASK_WAIT_SENSOR_QUICK_READ(u16_thermometerValue);
    //pop the oldest value
    uint16_t i = 0;
    for(i;i<(samples);i++){
      temp_val_array[i]=temp_val_array[i+1];
    }
    //add the newest
    temp_val_array[samples-1] = u16_thermometerValue;
    //DEBUG
    ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
    if(mode == 1){
      //oneshot
      ESOS_TASK_WAIT_SENSOR_QUICK_READ(u16_thermometerValue);
      output = u16_thermometerValue;
    }else if (mode == 2){
      //avg
      uint16_t total = 0;
      uint16_t i = 0;
      for(i;i<(samples);i++){
        total += temp_val_array[i];
      }
      //set the value for output. Overwrite the most recent read value.
      output = (total / samples);
    }else if (mode == 3){
      //min
      output=temp_val_array[0];
      uint16_t i = 1;
      for(i;i<samples;i++){
        if(temp_val_array[i]<output){
          output=temp_val_array[i];
        }
      }
    }else if (mode == 4){
      //max
      output=temp_val_array[0];
      uint16_t i = 1;
      for(i;i<samples;i++){
        if(temp_val_array[i]>output){
          output=temp_val_array[i];
        }
      }
    }else if (mode == 5){
      //med
      uint16_t x = 0;
      uint16_t y = 0;
      uint16_t temp;
      for(x; x<samples; x++){
        for(y; y<samples-1;y++){
          if(temp_val_array[y]>temp_val_array[y+1]){
            temp = temp_val_array[y];
            temp_val_array[y] = temp_val_array[y+1];
            temp_val_array[y+1] = temp;
          }
        }
      }
      output = (temp_val_array[(samples-1)/2]+temp_val_array[samples/2])/2;
    }

    // publish reading
    char read [] = "\nThermometer Reading: ";

    output = adc_to_celsius(output);
    // uint16_to_string(output);

    ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
    ESOS_TASK_WAIT_ON_SEND_STRING(read);
    // ESOS_TASK_WAIT_ON_SEND_STRING(_st_esos_uiF14Data.u16_string);
    ESOS_TASK_WAIT_ON_SEND_UINT32_AS_HEX_STRING((output << 16) + 0);
    ESOS_TASK_WAIT_ON_SEND_STRING(" degrees C");
    ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

    ESOS_TASK_WAIT_UNTIL_UIF14_SW1_RELEASED();
  }
  ESOS_TASK_END();
}

// Enables/disables the 1 second read/output loop
ESOS_USER_TASK(SW2_READ_TEMP){
  ESOS_TASK_BEGIN();
  while(TRUE){
    ESOS_TASK_WAIT_UNTIL_UIF14_SW2_PRESSED();
    ESOS_TASK_WAIT_UNTIL_UIF14_SW2_RELEASED();
    output_sw2 = TRUE;
    ESOS_TASK_WAIT_UNTIL(esos_uiF14_isSW1Pressed() || esos_uiF14_isSW2Pressed() || esos_uiF14_isSW3Pressed());
    output_sw2 = FALSE;
    ESOS_TASK_WAIT_UNTIL(esos_uiF14_isSW1Released() && esos_uiF14_isSW2Released() && esos_uiF14_isSW3Released());
  }
  ESOS_TASK_END();
}

// Task to display output of thermometer every 1 second
ESOS_USER_TASK(SW2_OUTPUT){
  ESOS_TASK_BEGIN();
  while(TRUE){
    while(output_sw2)
    {
      ESOS_TASK_WAIT_SENSOR_QUICK_READ(u16_thermometerValue);
      //pop the oldest value
      uint16_t i = 0;
      for(i;i<(samples);i++){
        temp_val_array[i]=temp_val_array[i+1];
      }
      //add the newest
      temp_val_array[samples-1] = u16_thermometerValue;
      if(mode == 1){
        //oneshot
        ESOS_TASK_WAIT_SENSOR_QUICK_READ(u16_thermometerValue);
        output = u16_thermometerValue;
      }else if (mode == 2){
        //avg
        uint16_t total = 0;
        uint16_t i = 0;
        for(i;i<(samples);i++){
          total += temp_val_array[i];
        }
        //set the value for output. Overwrite the most recent read value.
        output = (total / samples);
      }else if (mode == 3){
        //min
        output=temp_val_array[0];
        uint16_t i = 1;
        for(i;i<samples;i++){
          if(temp_val_array[i]<output){
            output=temp_val_array[i];
          }
        }
      }else if (mode == 4){
        //max
        output=temp_val_array[0];
        uint16_t i = 1;
        for(i;i<samples;i++){
          if(temp_val_array[i]>output){
            output=temp_val_array[i];
          }
        }
      }else if (mode == 5){
        //med
        uint16_t x = 0;
        uint16_t y = 0;
        uint16_t temp;
        for(x; x<samples; x++){
          for(y; y<samples-1;y++){
            if(temp_val_array[y]>temp_val_array[y+1]){
              temp = temp_val_array[y];
              temp_val_array[y] = temp_val_array[y+1];
              temp_val_array[y+1] = temp;
            }
          }
        }
        output = (temp_val_array[(samples-1)/2]+temp_val_array[samples/2])/2;
      }

      // publish reading
      char read [] = "\nThermometer Reading: ";

      output = adc_to_celsius(output);
      // uint16_to_string(output);

      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING(read);
      // ESOS_TASK_WAIT_ON_SEND_STRING(_st_esos_uiF14Data.u16_string);
      ESOS_TASK_WAIT_ON_SEND_UINT32_AS_HEX_STRING((output << 16) + 0);
      ESOS_TASK_WAIT_ON_SEND_STRING(" degrees C");
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      
      ESOS_TASK_WAIT_TICKS(1000);
    }
    ESOS_TASK_YIELD();
  }
  ESOS_TASK_END();
}

// Presents a UI to the user to select operation modes
ESOS_USER_TASK(SW3_UI_TASK) {
  static uint8_t single_char;
  static uint8_t single_char2;
  static uint8_t choice;
  static uint8_t choice2;
  ESOS_TASK_BEGIN();
  while(TRUE) {
    ESOS_TASK_WAIT_UNTIL_UIF14_SW3_PRESSED();
    char str[] = "\nEnter Processing Mode.\n1. one-shot\n2. average\n3. minumum\n4. maximum\n5. median\n";
    char str2[] = "\nBEEP BOP BRRRRRRR. Invalid value!\n";
    char str3[] = "\nNumber of Samples?\n1. two\n2. four\n3. eight\n4. sixteen\n5. thirty-two\n6. sixty-four\n";
  
    ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
    ESOS_TASK_WAIT_ON_SEND_STRING(str);
    ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

    ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
    ESOS_TASK_WAIT_ON_GET_UINT8(single_char);
    ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();
    choice = single_char;
    ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
    ESOS_TASK_WAIT_ON_SEND_UINT8(choice);
    ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
    BOOL isOption = choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5';
  
    // Numerical Input
    if (isOption){
      ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING(str3);
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      //User Choice 2
      ESOS_TASK_WAIT_ON_GET_UINT8(single_char2);
      ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();
      choice2 = single_char2;
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_UINT8(choice2);
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      BOOL isOption2 = choice2 == '1' || choice2 == '2' || choice2 == '3' || choice2 == '4' || choice2 == '5' || choice2 == '6';
      
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING("\nChoices are ");
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      if(isOption2)
      {
        if(choice2 == '1'){
          samples = 2;
        } else if (choice2 == '2'){
          samples = 4;
        } else if (choice2 == '3'){
          samples = 8;
        } else if (choice2 == '4'){
          samples = 16;
        } else if (choice2 == '5'){
          samples = 32;
        } else if (choice2 == '6'){
          samples = 64;
        }
        //need to reset the array of values when we set something
        uint16_t x = 0;
        for(x; x<samples;x++){
          temp_val_array[x]=u16_thermometerValue;
        }
        if(choice == '1'){
          //set oneshot
          mode = 1;
          samples = 1;
        } else if (choice == '2') {
          //set average
          mode = 2;
        } else if (choice == '3') {
          //set minimum
          mode = 3;
        } else if (choice == '4') {
          //set maximum
          mode = 4;
        } else if (choice == '5') {
          mode = 5;
          //set median
        } else {
          // error message
          ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
          ESOS_TASK_WAIT_ON_SEND_STRING(str2);
          ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        // display the user choice
        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_UINT8(choice);
        ESOS_TASK_WAIT_ON_SEND_STRING(" and ");
        ESOS_TASK_WAIT_ON_SEND_UINT8(choice2);
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      }
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_WAIT_ON_SEND_STRING("\n");
      ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      ESOS_TASK_YIELD();
    }
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
  CONFIG_SW3();
  CONFIG_TEMP();

  config_esos_uiF14();
  esos_sensor_config_hw(TEMP_ADC_CHANNEL, 0); // configures ADC for thermometer readings

  esos_uiF14_flashLED3(250); // heartbeat LED
  samples = 1;
  mode = 1;
  //Need new input task
  esos_RegisterTask(SW1_READ_TEMP);
  esos_RegisterTask(SW2_READ_TEMP);
  esos_RegisterTask(SW2_OUTPUT);
  esos_RegisterTask(SW3_UI_TASK);

} // end user_init()