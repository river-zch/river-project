#include "foc_Calibration.h"
#include "foc_math.h"
#include "mt6816.h"
#include "foc_app.h"
uint8_t flag_test=0;
volatile float self_angle = 0 , spi_pulse ,theta_angle;

void Calibration_Zero(void)
{
	
    spi_pulse = MT6816_Get_AngleData() ;
    //角度相关
    self_angle += 0.1f;
    if (self_angle > 360)
        self_angle = 0;

    theta_angle = self_angle*PI/180.0f;
    //坐标变换
    qd_t tempqt={.q=0.5f,.d=0};
		FOC_PWM_Run(&FOC_MOTOR.pwm, tempqt,theta_angle);

}


