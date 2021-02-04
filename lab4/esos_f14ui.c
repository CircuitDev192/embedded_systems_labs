/*******************************************************************
 * 
 * C code framework for ESOS user-interface (UI) service
 * 
 *    requires the EMBEDDED SYSTEMS target rev. F14
 * 
 * ****************************************************************/
# include "revF14.h"
# include "esos_f14ui.h"

// PRIVATE FUNCTIONS
inline void _esos_uiF14_setRPGCounter (uint16_t newValue) {
    _st_esos_uiF14Data.u16_RPGCounter = newValue;
}

// PUBLIC SWITCH FUNCTIONS
inline BOOL esos_uiF14_isSW1Pressed (void) {
    return (_st_esos_uiF14Data.b_SW1Pressed==TRUE);
}

inline BOOL esos_uiF14_isSW1Released (void) {
    return (_st_esos_uiF14Data.b_SW1Pressed==FALSE);
}

inline BOOL esos_uiF14_isSW1DoublePressed (void) {
    return (_st_esos_uiF14Data.b_SW1DoublePressed==TRUE);
}

inline BOOL esos_uiF14_isSW2Pressed (void) {
    return (_st_esos_uiF14Data.b_SW2Pressed==TRUE);
}

inline BOOL esos_uiF14_isSW2Released (void) {
    return (_st_esos_uiF14Data.b_SW2Pressed==FALSE);
}

inline BOOL esos_uiF14_isSW2DoublePressed (void) {
    return (_st_esos_uiF14Data.b_SW2DoublePressed==TRUE);
}

inline BOOL esos_uiF14_isSW3Pressed (void) {
    return (_st_esos_uiF14Data.b_SW3Pressed==TRUE);
}

inline BOOL esos_uiF14_isSW3Released (void) {
    return (_st_esos_uiF14Data.b_SW3Pressed==FALSE);
}

inline BOOL esos_uiF14_isSW3DoublePressed (void) {
    return (_st_esos_uiF14Data.b_SW3DoublePressed==TRUE);
}

inline void esos_uiF14_setSW1DoublePressPeriod(uint16_t value)
{
    _st_esos_uiF14Data.u16_doublePressPeriodSW1 = value;
}

inline void esos_uiF14_setSW2DoublePressPeriod(uint16_t value)
{
    _st_esos_uiF14Data.u16_doublePressPeriodSW2 = value;
}

inline void esos_uiF14_setSW3DoublePressPeriod(uint16_t value)
{
    _st_esos_uiF14Data.u16_doublePressPeriodSW3 = value;
}

// PUBLIC LED FUNCTIONS

// LED 1
inline BOOL esos_uiF14_isLED1On (void) {
    return (_st_esos_uiF14Data.b_LED1On==TRUE);
}

inline BOOL esos_uiF14_isLED1Off (void) {
    return (_st_esos_uiF14Data.b_LED1On==FALSE);
}

inline void esos_uiF14_turnLED1On (void) {
    _st_esos_uiF14Data.b_LED1On = TRUE;
    _st_esos_uiF14Data.u16_LED1FlashPeriod = 0;
}

inline void esos_uiF14_turnLED1Off (void) {
    _st_esos_uiF14Data.b_LED1On = FALSE;
    _st_esos_uiF14Data.u16_LED1FlashPeriod = 0;
}

inline void esos_uiF14_toggleLED1 (void) {
    _st_esos_uiF14Data.b_LED1On ^= 1;
}

inline void esos_uiF14_flashLED1( uint16_t u16_period ) {
    _st_esos_uiF14Data.u16_LED1FlashPeriod = u16_period;
}

// LED 2
inline BOOL esos_uiF14_isLED2On (void) {
    return (_st_esos_uiF14Data.b_LED2On==TRUE);
}

inline BOOL esos_uiF14_isLED2Off (void) {
    return (_st_esos_uiF14Data.b_LED2On==FALSE);
}

inline void esos_uiF14_turnLED2On (void) {
    _st_esos_uiF14Data.b_LED2On = TRUE;
    _st_esos_uiF14Data.u16_LED2FlashPeriod = 0;
}

inline void esos_uiF14_turnLED2Off (void) {
    _st_esos_uiF14Data.b_LED2On = FALSE;
    _st_esos_uiF14Data.u16_LED2FlashPeriod = 0;
}

inline void esos_uiF14_toggleLED2 (void) {
    _st_esos_uiF14Data.b_LED2On ^= 1;
}

inline void esos_uiF14_flashLED2( uint16_t u16_period) {
    _st_esos_uiF14Data.u16_LED2FlashPeriod = u16_period;
}

// LED 3
inline BOOL esos_uiF14_isLED3On (void) {
    return (_st_esos_uiF14Data.b_LED3On==TRUE);
}

inline BOOL esos_uiF14_isLED3Off (void) {
    return (_st_esos_uiF14Data.b_LED3On==FALSE);
}

inline void esos_uiF14_turnLED3On (void) {
    _st_esos_uiF14Data.b_LED3On = TRUE;
    _st_esos_uiF14Data.u16_LED3FlashPeriod = 0;
}

inline void esos_uiF14_turnLED3Off (void) {
    _st_esos_uiF14Data.b_LED3On = FALSE;
    _st_esos_uiF14Data.u16_LED3FlashPeriod = 0;
}

inline void esos_uiF14_toggleLED3 (void) {
    _st_esos_uiF14Data.b_LED3On ^= 1;
}

inline void esos_uiF14_flashLED3( uint16_t u16_period) {
    _st_esos_uiF14Data.u16_LED3FlashPeriod = u16_period;
}

// LED Red (1)
inline void esos_uiF14_turnRedLEDOn (void) {
    _st_esos_uiF14Data.b_LED1On = TRUE;
}

inline void esos_uiF14_turnRedLEDOff (void) {
    _st_esos_uiF14Data.b_LED1On = FALSE;
}

// LED Yellow (2)
inline void esos_uiF14_turnYellowLEDOn (void) {
    _st_esos_uiF14Data.b_LED2On = TRUE;
}

inline void esos_uiF14_turnYellowLEDOff (void) {
    _st_esos_uiF14Data.b_LED2On = FALSE;
}

// LED Green (3)
inline void esos_uiF14_turnGreenLEDOn (void) {
    _st_esos_uiF14Data.b_LED3On = TRUE;
}

inline void esos_uiF14_turnGreenLEDOff (void) {
    _st_esos_uiF14Data.b_LED3On = FALSE;
}

// PUBLIC RPG FUNCTIONS
inline uint16_t esos_uiF14_getRPGValue_u16 ( void ) {
    return _st_esos_uiF14Data.u16_RPGCounter;
}

inline BOOL esos_uiF14_isRPGTurning ( void ) {
    return (esos_uiF14_getRPGVelocity_i16() != 0 && _st_esos_uiF14Data.u16_RPGCounter < _st_esos_uiF14Data.u16_RPGSlowSpeed);
}

inline BOOL esos_uiF14_isRPGTurningSlow( void ) {
  return _st_esos_uiF14Data.b_isRPGSlow;
}

inline BOOL esos_uiF14_isRPGTurningMedium( void ) {
  return _st_esos_uiF14Data.b_isRPGMedium;
}

inline BOOL esos_uiF14_isRPGTurningFast( void ) {
  return _st_esos_uiF14Data.b_isRPGFast;
}

// sets RPG Slow speed period, error checks against medium speed
inline void esos_uiF14_setRPGTurningSlow( uint16_t speed) {
  if (speed <= _st_esos_uiF14Data.u16_RPGMediumSpeed) return;
  _st_esos_uiF14Data.u16_RPGSlowSpeed = speed;
}

// sets RPG Medium speed period, error checks against slow and fast speed
inline void esos_uiF14_setRPGTurningMedium( uint16_t speed) {
  if (speed >= _st_esos_uiF14Data.u16_RPGSlowSpeed) return;
  if (speed <= _st_esos_uiF14Data.u16_RPGFastSpeed) return;
  _st_esos_uiF14Data.u16_RPGMediumSpeed = speed;
}

// sets RPG Fast speed period, error checks against medium speed
inline void esos_uiF14_setRPGTurningFast( uint16_t speed) {
  if (speed >= _st_esos_uiF14Data.u16_RPGMediumSpeed) return;
  _st_esos_uiF14Data.u16_RPGFastSpeed = speed;
}

inline BOOL esos_uiF14_isRPGTurningCW( void ) {
  return (esos_uiF14_getRPGVelocity_i16() > 0);
}

inline BOOL esos_uiF14_isRPGTurningCCW( void ) {
  return (esos_uiF14_getRPGVelocity_i16() < 0);
}

// should return 0, -1 for CCW, 1 for CW
inline int16_t esos_uiF14_getRPGVelocity_i16( void ) {
  return _st_esos_uiF14Data.i16_RPGVelocity;
}

// Utility function for parsing an integer value from the user
inline int16_t esos_uiF14_parseValue_i16( uint8_t* array, uint8_t length )
{
    uint8_t i = 0;
    int16_t parsedInt = 0;
    while (i < length) {
        parsedInt += (array[i]-48)*pow(10, length-i-1);
        i += 1;
    }
    return parsedInt;
}

// Math utility pow() function calculates a number rased to a power recursively
inline int16_t pow(int16_t base, int16_t exp)
{
    if (exp <= 0){
        return 1;
    }
    else
    {
        return base*pow(base, exp - 1);
    }
}

// converts ADC reading from temperature sensor to degrees Celsius
inline uint16_t adc_to_celsius(uint16_t adc_raw)
{
    uint32_t val = (adc_raw*165) >> 9; 
    return val-34;
}

// convert int16_t to char array
inline void uint16_to_string(uint16_t value)
{
    uint8_t i=0;
    for (i; i<20; i+=1)
    {
        _st_esos_uiF14Data.u16_string[i] = 0;
    }
    if (value == 0)
    {
        _st_esos_uiF14Data.u16_string[0] = 48;
    } else
    {
        i = 0;
        uint8_t dec = 5;
        BOOL num_start = FALSE;
        while (TRUE)
        {
            uint16_t power = pow(10, dec);
            uint16_t num = value / power;
            if (num != 0) num_start = TRUE;
            if (num_start) {
                _st_esos_uiF14Data.u16_string[i] = num + 48;
                i += 1;
                value -= num*power;
            }
            dec -= 1;
            if (dec == 255) break;
        }
    }
}

// UIF14 task to manage user-interface
ESOS_USER_TASK( __esos_uiF14_task ){
  
  ESOS_TASK_BEGIN();
  while(TRUE) {
    // Reset Double Press
    _st_esos_uiF14Data.b_SW1DoublePressed = 0;
    _st_esos_uiF14Data.b_SW2DoublePressed = 0;
    _st_esos_uiF14Data.b_SW3DoublePressed = 0;

    // Debouncing switches from 10 ms delay
    BOOL SW1_changed = _st_esos_uiF14Data.b_SW1Pressed == SW1;
    _st_esos_uiF14Data.b_SW1Pressed = !SW1;
    BOOL SW2_changed = _st_esos_uiF14Data.b_SW2Pressed == SW2;
    _st_esos_uiF14Data.b_SW2Pressed = !SW2;
    BOOL SW3_changed = _st_esos_uiF14Data.b_SW3Pressed == SW3;
    _st_esos_uiF14Data.b_SW3Pressed = !SW3;

    // LED Handling
    if (_st_esos_uiF14Data.u16_LED1FlashPeriod != 0)
    {
        _st_esos_uiF14Data.u16_LED1FlashCounter += __ESOS_UIF14_UI_PERIOD_MS*2;
        if (_st_esos_uiF14Data.u16_LED1FlashCounter >= _st_esos_uiF14Data.u16_LED1FlashPeriod)
        {
            _st_esos_uiF14Data.u16_LED1FlashCounter = 0;
            esos_uiF14_toggleLED1();
        }
    }
    if (_st_esos_uiF14Data.u16_LED2FlashPeriod != 0)
    {
        _st_esos_uiF14Data.u16_LED2FlashCounter += __ESOS_UIF14_UI_PERIOD_MS*2;
        if (_st_esos_uiF14Data.u16_LED2FlashCounter >= _st_esos_uiF14Data.u16_LED2FlashPeriod)
        {
            _st_esos_uiF14Data.u16_LED2FlashCounter = 0;
            esos_uiF14_toggleLED2();
        }
    }
    if (_st_esos_uiF14Data.u16_LED3FlashPeriod != 0)
    {
        _st_esos_uiF14Data.u16_LED3FlashCounter += __ESOS_UIF14_UI_PERIOD_MS*2;
        if (_st_esos_uiF14Data.u16_LED3FlashCounter >= _st_esos_uiF14Data.u16_LED3FlashPeriod)
        {
            _st_esos_uiF14Data.u16_LED3FlashCounter = 0;
            esos_uiF14_toggleLED3();
        }
    }
    LED1 = _st_esos_uiF14Data.b_LED1On;
    LED2 = _st_esos_uiF14Data.b_LED2On;
    LED3 = _st_esos_uiF14Data.b_LED3On;

    // RPG Handling
    _st_esos_uiF14Data.u16_RPGCounter += __ESOS_UIF14_UI_PERIOD_MS;
    if (_st_esos_uiF14Data.u16_RPGCounter >= 65500) _st_esos_uiF14Data.u16_RPGCounter = 65500;
    if (RPGA != RPGB && _st_esos_uiF14Data.u16_RPGCounter >= _st_esos_uiF14Data.u16_RPGFastSpeed) // RPG is triggered
    {
        _st_esos_uiF14Data.u16_RPGCounter = _st_esos_uiF14Data.u16_RPGCounter - _st_esos_uiF14Data.u16_lastRPGCounter;
        _st_esos_uiF14Data.u16_lastRPGCounter = _st_esos_uiF14Data.u16_RPGCounter;
        // Velocity/Direction of RPG
        if (_st_esos_uiF14Data.b_RPGAHigh == RPGB)
        {
            _st_esos_uiF14Data.i16_RPGVelocity = -1;
        } else
        {
            _st_esos_uiF14Data.i16_RPGVelocity = 1;
        }
        _st_esos_uiF14Data.b_RPGAHigh = RPGA;
        _st_esos_uiF14Data.b_RPGBHigh = RPGB;
    } else
    {
        // not turning
        _st_esos_uiF14Data.i16_RPGVelocity = 0;
    }

    // Handle RPG Speed
    if (_st_esos_uiF14Data.u16_RPGCounter <= _st_esos_uiF14Data.u16_RPGFastSpeed)
    {
        _st_esos_uiF14Data.b_isRPGFast = TRUE;
        _st_esos_uiF14Data.b_isRPGMedium = FALSE;
        _st_esos_uiF14Data.b_isRPGSlow = FALSE;
    } else if ( _st_esos_uiF14Data.u16_RPGCounter > _st_esos_uiF14Data.u16_RPGFastSpeed \
            && _st_esos_uiF14Data.u16_RPGCounter <= _st_esos_uiF14Data.u16_RPGMediumSpeed)
    {
        _st_esos_uiF14Data.b_isRPGFast = FALSE;
        _st_esos_uiF14Data.b_isRPGMedium = TRUE;
        _st_esos_uiF14Data.b_isRPGSlow = FALSE;
    } else if ( _st_esos_uiF14Data.u16_RPGCounter > _st_esos_uiF14Data.u16_RPGMediumSpeed \
            && _st_esos_uiF14Data.u16_RPGCounter <= _st_esos_uiF14Data.u16_RPGSlowSpeed)
    {
        _st_esos_uiF14Data.b_isRPGFast = FALSE;
        _st_esos_uiF14Data.b_isRPGMedium = FALSE;
        _st_esos_uiF14Data.b_isRPGSlow = TRUE;
    } else
    {
        _st_esos_uiF14Data.b_isRPGFast = FALSE;
        _st_esos_uiF14Data.b_isRPGMedium = FALSE;
        _st_esos_uiF14Data.b_isRPGSlow = FALSE;
    }
    

    // Double Press Detection for SW1
    if (esos_uiF14_isSW1Released() && SW1_changed && _st_esos_uiF14Data.u16_timeBetweenSW1Presses >= _st_esos_uiF14Data.u16_doublePressPeriodSW1) //Testing  if the time between presses is greater than the 
    {                                                                                   // 10ms UI Period * __ESOS_DOUBLE_PRESS_TIME_MULT
        //button was not double pressed in time, reset timer
        _st_esos_uiF14Data.u16_timeBetweenSW1Presses = 0;
        _st_esos_uiF14Data.b_SW1DoublePressed = 0;
    } 
    else if (esos_uiF14_isSW1Pressed() && SW1_changed \
                    && _st_esos_uiF14Data.u16_timeBetweenSW1Presses <= _st_esos_uiF14Data.u16_doublePressPeriodSW1 \
                    && _st_esos_uiF14Data.u16_timeBetweenSW1Presses >= 20)
    {
        //called if the button has been double pressed
        _st_esos_uiF14Data.u16_timeBetweenSW1Presses = 0;
        _st_esos_uiF14Data.b_SW1DoublePressed = 1;
    }

    // Double Press Detection for SW2
    if (esos_uiF14_isSW2Released() && SW2_changed && _st_esos_uiF14Data.u16_timeBetweenSW2Presses >= _st_esos_uiF14Data.u16_doublePressPeriodSW2) //Testing  if the time between presses is greater than the 
    {                                                                                   // 10ms UI Period * __ESOS_DOUBLE_PRESS_TIME_MULT
        //button was not double pressed in time, reset timer
        _st_esos_uiF14Data.u16_timeBetweenSW2Presses = 0;
        _st_esos_uiF14Data.b_SW2DoublePressed = 0;
    } 
    else if (esos_uiF14_isSW2Pressed() && SW2_changed \
                    && _st_esos_uiF14Data.u16_timeBetweenSW2Presses <= _st_esos_uiF14Data.u16_doublePressPeriodSW2 \
                    && _st_esos_uiF14Data.u16_timeBetweenSW2Presses >= 20)
    {
        //called if the button has been double pressed
        _st_esos_uiF14Data.u16_timeBetweenSW2Presses = 0;
        _st_esos_uiF14Data.b_SW2DoublePressed = 1;
    }

    // Double Press Detection for SW3
    if (esos_uiF14_isSW3Released() && SW3_changed && _st_esos_uiF14Data.u16_timeBetweenSW3Presses >= _st_esos_uiF14Data.u16_doublePressPeriodSW3) //Testing  if the time between presses is greater than the 
    {                                                                                   // 10ms UI Period * __ESOS_DOUBLE_PRESS_TIME_MULT
        //button was not double pressed in time, reset timer
        _st_esos_uiF14Data.u16_timeBetweenSW3Presses = 0;
        _st_esos_uiF14Data.b_SW3DoublePressed = 0;
    } 
    else if (esos_uiF14_isSW3Pressed() && SW3_changed \
                    && _st_esos_uiF14Data.u16_timeBetweenSW3Presses <= _st_esos_uiF14Data.u16_doublePressPeriodSW3 \
                    && _st_esos_uiF14Data.u16_timeBetweenSW3Presses >= 20)
    {
        //called if the button has been double pressed
        _st_esos_uiF14Data.u16_timeBetweenSW3Presses = 0;
        _st_esos_uiF14Data.b_SW3DoublePressed = 1;
    }

    //Regardless of whether or not a button was pressed, increase the counter for each of them
    _st_esos_uiF14Data.u16_timeBetweenSW1Presses += __ESOS_UIF14_UI_PERIOD_MS;
    _st_esos_uiF14Data.u16_timeBetweenSW2Presses += __ESOS_UIF14_UI_PERIOD_MS;
    _st_esos_uiF14Data.u16_timeBetweenSW3Presses += __ESOS_UIF14_UI_PERIOD_MS;

    ESOS_TASK_WAIT_TICKS( __ESOS_UIF14_UI_PERIOD_MS );
  }
  ESOS_TASK_END();
}

// UIF14 INITIALIZATION FUNCTION

void config_esos_uiF14( void ) {
  // setup your UI implementation
  esos_RegisterTask( __esos_uiF14_task );
  _st_esos_uiF14Data.u16_LED1FlashPeriod = 0;
  _st_esos_uiF14Data.u16_LED2FlashPeriod = 0;
  _st_esos_uiF14Data.u16_LED3FlashPeriod = 0;
  _st_esos_uiF14Data.u16_LED1FlashCounter = 0;
  _st_esos_uiF14Data.u16_LED2FlashCounter = 0;
  _st_esos_uiF14Data.u16_LED3FlashCounter = 0;
  _st_esos_uiF14Data.u16_timeBetweenSW1Presses = 0;
  _st_esos_uiF14Data.u16_timeBetweenSW2Presses = 0;
  _st_esos_uiF14Data.u16_timeBetweenSW3Presses = 0;

  _st_esos_uiF14Data.u16_RPGFastSpeed = 200; // 200ms
  _st_esos_uiF14Data.u16_RPGMediumSpeed = 1500; // 1.5s    These values chosen to give room for error when turning the RPG for demonstration
  _st_esos_uiF14Data.u16_RPGSlowSpeed = 3000; // 3s
  _st_esos_uiF14Data.u16_RPGCounter = _st_esos_uiF14Data.u16_RPGSlowSpeed; // initialized to slowest value
  _st_esos_uiF14Data.u16_lastRPGCounter = _st_esos_uiF14Data.u16_RPGSlowSpeed;
  // These hold the state of the RPG
  _st_esos_uiF14Data.b_isRPGSlow = FALSE;
  _st_esos_uiF14Data.b_isRPGMedium = FALSE;
  _st_esos_uiF14Data.b_isRPGFast = FALSE;
  // These set the default value of double press to 300 ms after testing was done for natural feeling.
  _st_esos_uiF14Data.u16_doublePressPeriodSW1 = __ESOS_DOUBLE_PRESS_TIME_MULT;
  _st_esos_uiF14Data.u16_doublePressPeriodSW2 = __ESOS_DOUBLE_PRESS_TIME_MULT;
  _st_esos_uiF14Data.u16_doublePressPeriodSW3 = __ESOS_DOUBLE_PRESS_TIME_MULT;
}