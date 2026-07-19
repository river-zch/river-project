#ifndef _FOC_CALIBRATION_H
#define _FOC_CALIBRATION_H

#include "foc_math.h"
#include "mt6816.h"
extern volatile float self_angle, spi_pulse ,theta_angle;
extern uint8_t flag_test;

void Calibration_Zero(void);



#endif

