#include "debug.h"

#include "usart.h"
#include "bsp.h"
#include "debug.h"
#include <stdlib.h>
#include "foc_app.h"
#include "mt6816.h"
#include "foc_motor.h"

/*vofa֡*/
VOFA_Send_Handle_t VOFA_Handle = {
    .tail = {0x00, 0x00, 0x80, 0x7f},
};

void Debug_Task(void)
{
	  
    VOFA_Handle.fdata[0] = FOC_MOTOR.pwm.Uabc.a;
    VOFA_Handle.fdata[1] = FOC_MOTOR.pwm.Uabc.b;
    VOFA_Handle.fdata[2] = FOC_MOTOR.pwm.Uabc.c;
    VOFA_Handle.fdata[3] = FOC_MOTOR.pwm.Ualpha_beta.alpha+10;
    VOFA_Handle.fdata[4] = FOC_MOTOR.pwm.Ualpha_beta.beta+10;
    VOFA_Handle.fdata[5] = FOC_MOTOR.pwm.Uqd.q;
    VOFA_Handle.fdata[6] = FOC_MOTOR.pwm.Uqd.d;
    VOFA_Handle.fdata[7] = FOC_MOTOR.pwm.ElAngle;
    VOFA_Handle.fdata[8] = flag_test;
    VOFA_Handle.fdata[9] = spi_pulse;
    VOFA_Handle.fdata[10] = self_angle;

    HAL_UART_Transmit(&huart3 ,(uint8_t*)&VOFA_Handle, sizeof(VOFA_Handle), 50);
}


