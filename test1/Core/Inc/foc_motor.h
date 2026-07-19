#ifndef _FOC_MOTOR_H
#define _FOC_MOTOR_H

#include <stdint.h>

#include  "foc_type.h"
#include  "foc_pwm.h"
#include "foc_vf.h"
#include "foc_Calibration.h"

/* 电机状态 */
typedef enum
{
    MOTOR_ENC_RUN,                         /* 空闲 */
    MOTOR_MT_CALIB,                    /* 编码器校准对齐 */
    MOTOR_VF_RUN,                       /* VF运行 */
    
}MOTOR_State_t;


/*ṹ*/
typedef struct
{
    MOTOR_State_t motor_state;              /*״̬*/
    
    uint32_t        pole_pairs;             /**/
    float           power;                  /*ѹ*/

    qd_t            Uqd;
    float           ElAngle;
    float           step;
    FOC_PWM_t       pwm;                    /*pwmṹ*/

    FOC_VF_t        vf;                     /* vf控制结构体 */

    /* 编码器校准参数 */
    float           align_voltage;          /* 对齐电压 (标幺值) */
    uint32_t        align_ticks;            /* 对齐持续 tick 数 */
    uint32_t        align_counter;          /* 对齐计时器 */


}FOC_MOTOR_t;



void FOC_Motor_Init(FOC_MOTOR_t *foc_motor);
void FOC_Motor_Run(FOC_MOTOR_t *foc_motor);







#endif

