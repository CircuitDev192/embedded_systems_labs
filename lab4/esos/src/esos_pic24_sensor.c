/*** I N C L U D E S *************************************************/
#include "esos_pic24_sensor.h"
#include "esos_sensor.h"
#include "pic24_adc.h"

/*** T H E   C O D E *************************************************/

/*********************************************************
 * Public functions intended to be called by other files *
 *********************************************************/

/**
Configure and enable the sensor module for PIC24 hardware.
\param e_senCh   specifies sensor channel
\param e_senVRef specifies sensor voltage reference
\hideinitializer
 */
void esos_sensor_config_hw (esos_sensor_ch_t e_senCh, esos_sensor_vref_t e_senVRef)
{
  configADC1_ManualCH0((uint16_t) e_senCh, (uint8_t) 1, (uint8_t) FALSE);
}

/**
Determine truth of: the sensor is currently converting
\hideinitializer
 */
BOOL esos_sensor_is_converting_hw (void)
{
  return __esos_IsSystemFlagSet(__ESOS_SYS_ADC_IS_BUSY);
}

/**
Initiate a conversion for a configured sensor
\hideinitializer
 */
void esos_sensor_initiate_hw (void)
{
  AD1CON1bits.ADON = 1;   //turn on the ADC
}

/**
Receive the value from a conversion that has already been initiated
\hideinitializer
 */
uint16_t esos_sensor_getvalue_u16_hw (void)
{
  return convertADC1();
}

/**
Release any pending conversions for the sensor
\hideinitializer
 */
void esos_sensor_release_hw (void)
{
  AD1CON1bits.ADON = 0;   //turn off the ADC
}