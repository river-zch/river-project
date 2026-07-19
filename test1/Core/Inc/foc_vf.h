#ifndef _FOC_VF_H
#define _FOC_VF_H


#include "foc_type.h"


typedef struct{
    SPEED_t speed;

    qd_t Uqd;           /*输出电压*/

    float k;            /*v/f比例系数*/
    float step;         /*单次步进*/


    float Ts;           /*运行周期*/
}FOC_VF_t;


void FOC_VF_Init(FOC_VF_t *foc_vf, float pole_pairs, float Ts);
void FOC_VF_Angle_Calc(FOC_VF_t *foc_vf);
void FOC_VF_Speed_Calc(FOC_VF_t *foc_vf);





#endif


