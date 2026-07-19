#include "foc_motor.h"

#include "foc_math.h"

/**
 * @brief 电机结构体初始化
 * 
 * @param foc_motor 
 */
void FOC_Motor_Init(FOC_MOTOR_t *foc_motor)
{
    foc_motor->motor_state = MOTOR_MT_CALIB;
    foc_motor->Uqd.q = 0.5f;
    foc_motor->step = 0.01f;
}



/**
 * @brief VF强拖模式运行
 * 
 * @param foc_motor 
 */
void Motor_VF_RUN(FOC_MOTOR_t *foc_motor)
{
    FOC_VF_t *vf = &foc_motor->vf;


    FOC_VF_Angle_Calc(vf);                                          /*根据VF的系数来计算电角度*/

    FOC_PWM_Run(&foc_motor->pwm, vf->Uqd, vf->speed.ElAngle);

}






/**
 * @brief 运行电机状态机
 * 
 * @param foc_motor 
 */
#include "debug.h"
void FOC_Motor_Run(FOC_MOTOR_t *foc_motor)
{
	MOTOR_State_t state = foc_motor->motor_state;

    switch(state){
        case MOTOR_VF_RUN:
            Motor_VF_RUN(foc_motor);
						debug_send("MOTOR_VF_RUN");
				break;
				case MOTOR_ENC_RUN:
            
            break;
				case MOTOR_MT_CALIB:
						debug_send("MOTOR_MT_CALIB");									
						Calibration_Zero();
            break;
        default:
            break;
    }
    
}


