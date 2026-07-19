#include "foc_app.h"
#include <foc_hw.h>

#include <stdio.h>

#if 1

/*SPEED 2207 kv1700*/

FOC_MOTOR_t FOC_MOTOR = {

    .pole_pairs = 7,                                /*极对数*/
    .power = 24.0f,                                 /*供电电压*/

    .vf = {
        .Uqd.q = 0.5f,
        .k = 0.012965f,                              /*vf强拖系数*/
    },

};

#endif





/**
 * @brief FOC初始化
 * 
 */
void FOC_Init(void)
{
    /*定时器周期值*/
    uint32_t htim1_period = (htim1.Init.Period+1);                     
    
    /*定时器频率*/
    uint32_t htim1_freq = 170000000/(htim1.Init.Prescaler+1)/htim1_period;   
    printf("htim1_period: %d  htim1_freq: %d\r\n", htim1_period, htim1_freq);


    FOC_Motor_Init(&FOC_MOTOR);
    FOC_PWM_Init(&FOC_MOTOR.pwm, htim1_period, FOC_MOTOR.power);

    FOC_VF_Init(&FOC_MOTOR.vf, FOC_MOTOR.pole_pairs, 1.0f/(float)htim1_freq);

    HAL_Delay(1000);        /*让电容冲一下电*/
}

void FOC_DeInit(void)
{

}


/**
 * @brief FOC的运行状态机，PWM定时器->ADC采样->执行此函数
 * 
 */
void FOC_App_Run(void)
{
    /*电机状态机运行*/
    FOC_Motor_Run(&FOC_MOTOR);
}

