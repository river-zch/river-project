#ifndef _FOC_PWM_H
#define _FOC_PWM_H



#include "foc_type.h"



/*Foc pwm计算结构体*/
typedef struct
{

    qd_t Uqd;                           /* 输出Uqd*/
    abc_t Uabc;                         /* 输出三相Uabc*/
    abc_t T_abc;                        /* 周期的占空比*/
    alphabeta_t Ualpha_beta;

    float ElAngle;
    float power;                        /* 母线电压 */
    uint32_t Tpwm;                      /* 定时器的周期值*/


}FOC_PWM_t;


void FOC_PWM_Init(FOC_PWM_t *foc_pwm, uint32_t Tpwm, float power);
void FOC_PWM_Run(FOC_PWM_t *foc_pwm, qd_t Uqd, float ElAngle);


















#endif
