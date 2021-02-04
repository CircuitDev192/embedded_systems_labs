#ifndef ESOS_pic33_SENSOR_H
#define ESOS_pic33_SENSOR_H

/* I N C L U D E S **********************************************************/
#include <esos_pic24.h>
#include <esos_sensor.h>

/* P U B L I C  P R O T O T Y P E S *****************************************/
void esos_sensor_config_hw (esos_sensor_ch_t, esos_sensor_vref_t);
void esos_sensor_initiate_conversion_hw (void);
uint16_t esos_sensor_getvalue_u16_hw (void);
void esos_sensor_release_hw (void);
BOOL esos_sensor_is_converting_hw (void);

#endif
