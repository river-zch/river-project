/**
 ****************************************************************************************************
 * @file        foc_hw.c
 * @author      哔哩哔哩-Rebron大侠
 * @version     V0.0
 * @date        2025-010-16
 * @brief       该FOC库所调用的一些硬件接口
 * @license     MIT License
 *              Copyright (c) 2025 Reborn大侠
 *              允许任何人使用、复制、修改和分发该代码，但需保留此版权声明。
 ****************************************************************************************************
 */


#include "foc_hw.h"
#include "foc_math.h"
#include "foc_app.h"

/***************************************PWM硬件相关**************************************/

#include "tim.h"
/**
 * @brief PWM硬件初始化
 * 
 */
void FOC_PWM_HW_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim1);                          /*开启PWM的定时器周期中断*/

    A_H_SET_PWM(0);
    B_H_SET_PWM(0);
    C_H_SET_PWM(0);

    FOC_PWM_HW_ON_OFF(true,true,true,true,true,true);       /*打开硬件PWM*/

}

void FOC_PWM_HW_DeInit(void)
{   
    HAL_TIM_Base_Stop_IT(&htim1);      

    FOC_PWM_HW_ON_OFF(false,false,false,false,false,false);       /*关闭硬件PWM*/                    
                         
}

/**
 * @brief PWM硬件通道开关
 * 
 * @param A     A相上管通道
 * @param A_N   A相下管通道
 * @param B     B相上管通道
 * @param B_N   B相下管通道
 * @param C     C相下管通道
 * @param C_N   C相下管通道
 */
void FOC_PWM_HW_ON_OFF(bool A, bool A_N, bool B, bool B_N, bool C, bool C_N)
{
    if(A)   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    else    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);

    if(A_N) HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
    else    HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);

    if(B)   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    else    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);

    if(B_N) HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
    else    HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);

    if(C)   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    else    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);

    if(C_N) HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
    else    HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);


}




/***************************************中断相关**************************************/

static float x = 0;
abc_t Iabc;
alphabeta_t Ialphabeta;
qd_t Iqd;

void Clarke_Park_Debug(void)
{
    
    
    Iabc.a = arm_sin_f32(x);
    Iabc.b = arm_sin_f32(x + _PI_3*2.0f );    
    Iabc.c = arm_sin_f32(x + _PI_3*2.0f + _PI_3*2.0f);    

    x += 0.0009f;
    
    x = Limit_Angle(x);

    /*模拟生成三相正弦波*/

    Ialphabeta = FOC_Clarke(Iabc);

    Iqd = Foc_Park(Ialphabeta, atan2f(Ialphabeta.beta, Ialphabeta.alpha));

}

void RePark_ReClarke_Debug(void)
{
    x += 0.0009f;
    x = Limit_Angle(x);

    /*逆park变换*/
    Ialphabeta = FOC_Rev_Park(Iqd, x);

    /*逆克拉克变换*/
    Iabc = FOC_Rev_Clarke(Ialphabeta);

}



/*定时器周期中断*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{ 
    if(htim->Instance == TIM1){ /*10k Hz*/

        FOC_App_Run();
        return;
    }
}














