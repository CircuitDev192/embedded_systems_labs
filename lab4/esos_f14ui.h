/*******************************************************************
 * 
 * C header file for ESOS user-interface (UI) service
 * 
 *    requires the EMBEDDED SYSTEMS target rev. F14
 * 
 * ****************************************************************/

#ifndef   ESOS_UIF14_H
#define ESOS_UIF14_H

// STRUCTURES

typedef struct {
    BOOL b_SW1Pressed;
    BOOL b_SW1DoublePressed;
    BOOL b_SW2Pressed;
    BOOL b_SW2DoublePressed;    
    BOOL b_SW3Pressed;
    BOOL b_SW3DoublePressed;    

    uint16_t u16_timeBetweenSW1Presses;
    uint16_t u16_timeBetweenSW2Presses;
    uint16_t u16_timeBetweenSW3Presses;
    uint16_t u16_doublePressPeriodSW1;
    uint16_t u16_doublePressPeriodSW2;
    uint16_t u16_doublePressPeriodSW3;
    
    BOOL b_RPGAHigh;
    BOOL b_RPGBHigh;
    
    BOOL b_LED1On;
    uint16_t u16_LED1FlashPeriod;
    uint16_t u16_LED1FlashCounter;
    BOOL b_LED2On;
    uint16_t u16_LED2FlashPeriod;
    uint16_t u16_LED2FlashCounter;
    BOOL b_LED3On;
    uint16_t u16_LED3FlashPeriod;
    uint16_t u16_LED3FlashCounter;
    
    uint16_t u16_RPGCounter;
    uint16_t u16_lastRPGCounter;
    uint16_t u16_RPGSlowestSpeed;
    // upper bounds of periods for Slow, Medium, Fast speeds
    uint16_t u16_RPGSlowSpeed;
    uint16_t u16_RPGMediumSpeed;
    uint16_t u16_RPGFastSpeed;
    BOOL b_isRPGSlow;
    BOOL b_isRPGMedium;
    BOOL b_isRPGFast;
    int16_t i16_RPGVelocity;
    char u16_string [20];
} _st_esos_uiF14Data_t;

// DEFINEs and CONSTANTs
#define __ESOS_TICKS_TO_MS(x)           (x/1)
#define __ESOS_MS_TO_TICKS(x)           (x*1)
#define __ESOS_UIF14_UI_PERIOD_MS       10 // 10 ms
#define __ESOS_DOUBLE_PRESS_TIME_MULT   300 // 0.3 seconds default, feels most natural to user after testing

// PRIVATE DATA 
 
_st_esos_uiF14Data_t _st_esos_uiF14Data;

// PRIVATE FUNCTION PROTOTYPES

uint16_t esos_uiF14_getRPGCounter (void);
void esos_ui_setRPGCounter (uint16_t);

uint16_t esos_uiF14_getLastRPGCounter (void);
void esos_ui_setLastRPGCounter (uint16_t);

ESOS_USER_TASK (__uiF14_task);

// PUBLIC API FUNCTION PROTOTYPES

inline BOOL esos_uiF14_isSW1Pressed (void);
inline BOOL esos_uiF14_isSW1Released (void);
inline BOOL esos_uiF14_isSW1DoublePressed (void);

inline BOOL esos_uiF14_isSW2Pressed (void);
inline BOOL esos_uiF14_isSW2Released (void);
inline BOOL esos_uiF14_isSW2DoublePressed (void);

inline BOOL esos_uiF14_isSW3Pressed (void);
inline BOOL esos_uiF14_isSW3Released (void);
inline BOOL esos_uiF14_isSW3DoublePressed (void);

inline void esos_uiF14_setSW1DoublePressPeriod (uint16_t);
inline void esos_uiF14_setSW2DoublePressPeriod (uint16_t);
inline void esos_uiF14_setSW3DoublePressPeriod (uint16_t);

inline BOOL esos_uiF14_isRPGTurning (void);
inline BOOL esos_uiF14_isRPGTurningSlow (void);
inline BOOL esos_uiF14_isRPGTurningMedium (void);
inline BOOL esos_uiF14_isRPGTurningFast (void);
inline void esos_uiF14_setRPGTurningSlow(uint16_t);
inline void esos_uiF14_setRPGTurningMedium(uint16_t);
inline void esos_uiF14_setRPGTurningFast(uint16_t);
inline BOOL esos_uiF14_isRPGTurningCW (void);
inline BOOL esos_uiF14_isRPGTurningCCW (void);

inline void esos_uiF14_turnLED1On (void);
inline void esos_uiF14_turnLED1Off (void);
inline void esos_uiF14_toggleLED1 (void);
inline void esos_uiF14_flashLED1 (uint16_t);

inline void esos_uiF14_turnLED2On (void);
inline void esos_uiF14_turnLED2Off (void);
inline void esos_uiF14_toggleLED2 (void);
inline void esos_uiF14_flashLED2 (uint16_t);

inline void esos_uiF14_turnLED3On (void);
inline void esos_uiF14_turnLED3Off (void);
inline void esos_uiF14_toggleLED3 (void);
inline void esos_uiF14_flashLED3 (uint16_t);

inline void esos_uiF14_turnRedLEDOn (void);
inline void esos_uiF14_turnRedLEDOff (void);
inline void esos_uiF14_turnGreenLEDOn (void);
inline void esos_uiF14_turnGreenLEDOff (void);
inline void esos_uiF14_turnYellowLEDOn (void);
inline void esos_uiF14_turnYellowLEDOff (void);

inline uint16_t esos_uiF14_getRPGValue_u16 (void);

inline void config_esos_uiF14(void);
inline int16_t esos_uiF14_getRPGVelocity_i16 (void);
inline int16_t pow(int16_t, int16_t);
inline uint16_t adc_to_celsius(uint16_t);
inline void uint16_to_string(uint16_t);

// PUBLIC API ESOS TASK MACROS

#define ESOS_TASK_WAIT_UNTIL_UIF14_SW1_PRESSED()              ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW1Pressed() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW1_RELEASED()             ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW1Released() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW1_PRESSED_AND_RELEASED() do {  \
                            ESOS_TASK_WAIT_UNTIL_UIF14_SW1_PRESSED(); \
                            ESOS_TASK_WAIT_UNTIL_UIF14_SW1_RELEASED();\
                          } while (0) 
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW1_DOUBLE_PRESSED()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW1DoublePressed() )

#define ESOS_TASK_WAIT_UNTIL_UIF14_SW2_PRESSED()              ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW2Pressed() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW2_RELEASED()             ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW2Released() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW2_PRESSED_AND_RELEASED() do {    \
                            ESOS_TASK_WAIT_UNTIL_UIF14_SW2_PRESSED(); \
                            ESOS_TASK_WAIT_UNTIL_UIF14_SW2_RELEASED();\
                          } while (0) 
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW2_DOUBLE_PRESSED()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW2DoublePressed() )

#define ESOS_TASK_WAIT_UNTIL_UIF14_SW3_PRESSED()              ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW3Pressed() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW3_RELEASED()             ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW3Released() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW3_PRESSED_AND_RELEASED() do {    \
                            ESOS_TASK_WAIT_UNTIL_UIF14_SW3_PRESSED(); \
                            ESOS_TASK_WAIT_UNTIL_UIF14_SW3_RELEASED();\
                          } while (0) 
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW3_DOUBLE_PRESSED()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW3DoublePressed() )

#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_UNTIL_TURNS()          ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRpgTurning() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_UNTIL_TURNS_CW()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRpgTurningCW() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_UNTIL_TURNS_CCW()      ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRpgTurningCCW() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_SLOW()           ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRpgTurningSlow() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_SLOW_CW()        ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRpgTurningSlow() && esos_uiF14_isRpgTurningCW())
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_SLOW_CCW()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRpgTurningSlow() && esos_uiF14_isRpgTurningCCW())
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_MEDIUM()         ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRpgTurningMedium() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_MEDIUM_CW()      ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRpgTurningMedium() && esos_uiF14_isRpgTurningCW())
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_MEDIUM_CCW()     ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRpgTurningMedium() && esos_uiF14_isRpgTurningCCW())
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_FAST()           ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRpgTurningFast())
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_FAST_CW()        ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRpgTurningFast() && esos_uiF14_isRpgTurningCW())
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_FAST_CCW()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRpgTurningFast() && esos_uiF14_isRpgTurningCCW())
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_MAKES_REV(y)           uint8_t i = 0;\
                            while (i < y*12) {\
                              ESOS_TASK_WAIT_UNTIL_UIF14_RPG_UNTIL_TURNS();\
                              i+=1;\
                            }
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_MAKES_CW_REV(y)        uint8_t i = 0;\
                            while (i < y*12) {\
                              ESOS_TASK_WAIT_UNTIL_UIF14_RPG_UNTIL_TURNS_CW();\
                              i+=1;\
                            }
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_MAKES_CCW_REV(y)       uint8_t i = 0;\
                            while (i < y*12) {\
                              ESOS_TASK_WAIT_UNTIL_UIF14_RPG_UNTIL_TURNS_CCW();\
                              i+=1;\
                            }

// #define ESOS_GET_CHAR_U8(input)     ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();\
//                                     ESOS_TASK_WAIT_ON_GET_UINT8( input ); \
//                                     ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();
// #define ESOS_ECHO_CHAR_U8(input)    ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();\
//                                     ESOS_TASK_WAIT_ON_SEND_UINT8( input );\
//                                     ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

#endif    // ESOS_UIF14_H