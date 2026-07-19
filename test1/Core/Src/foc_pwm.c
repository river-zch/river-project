#include "foc_pwm.h"
#include "foc_math.h"
#include "foc_hw.h"



/**
 * @brief 输出SPWM
 * 
 * @param foc_pwm 
 * @param U_qd qd轴电压
 * @param angle_el 电角度
 */
static void FOC_RUN_SPWM(FOC_PWM_t *foc_pwm, qd_t U_qd, float angle_el)
{
    abc_t output             = {0};
    alphabeta_t input        = {0};

    float half_power = foc_pwm->power/2.0f;
    uint32_t Tpwm = foc_pwm->Tpwm/2;
    

    input = FOC_Rev_Park(U_qd, angle_el);
    // foc_pwm->Ualpha_beta.alpha = input.alpha *foc_pwm->power+half_power;
    // foc_pwm->Ualpha_beta.beta = input.beta *foc_pwm->power+half_power;
    foc_pwm->Ualpha_beta = input;

    /*克拉克逆变换*/
    output = FOC_Rev_Clarke(input);
    

    output.a += half_power;
    output.b += half_power;
    output.c += half_power;

    foc_pwm->Uabc = output;

    A_H_SET_PWM(output.a/foc_pwm->power *Tpwm);                     /*加上死区补偿*/
    B_H_SET_PWM(output.b/foc_pwm->power *Tpwm);
    C_H_SET_PWM(output.c/foc_pwm->power *Tpwm);
}


/**
 * @brief 运行pwm
 * 
 * @param foc_pwm 
 * @param Uqd qd轴电压
 * @param ElAngle 电角度
 */
void FOC_PWM_Run(FOC_PWM_t *foc_pwm, qd_t Uqd, float ElAngle)
{    

    foc_pwm->Uqd = Uqd;
    foc_pwm->ElAngle = ElAngle;

    /*使用spwm*/
    FOC_RUN_SPWM(foc_pwm, Uqd, ElAngle);
}

/**
 * @brief FOC SVWPM初始化
 * 
 * @param foc_pwm 
 * @param Tpwm 
 * @param power 
 */
void FOC_PWM_Init(FOC_PWM_t *foc_pwm, uint32_t Tpwm, float power)
{
    foc_pwm->Tpwm = Tpwm;
    foc_pwm->power = power;

    FOC_PWM_HW_Init();

}
void FOC_PWM_DeInit(FOC_PWM_t *foc_pwm)
{
    FOC_PWM_HW_DeInit();

}


