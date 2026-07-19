#ifndef _FOC_HW_H
#define _FOC_HW_H

#include <stdbool.h>
#include <stdint.h>

#include <tim.h>

/*PWM½Ó¿Ú*/
#define A_H_SET_PWM(x)       (htim1.Instance->CCR3 =x)
#define B_H_SET_PWM(x)       (htim1.Instance->CCR2 =x)
#define C_H_SET_PWM(x)       (htim1.Instance->CCR1 =x)
#define A_L_SET_PWM(x)       (x)
#define B_L_SET_PWM(x)       (x)
#define C_L_SET_PWM(x)       (x)

void FOC_PWM_HW_Init(void);
void FOC_PWM_HW_DeInit(void);
void FOC_PWM_HW_ON_OFF(bool A, bool A_N, bool B, bool B_N, bool C, bool C_N);





#endif

