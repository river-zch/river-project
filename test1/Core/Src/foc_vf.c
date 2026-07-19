#include "foc_vf.h"

#include "foc_math.h"

/**
 * @brief VF初始化
 * 
 * @param foc_vf 
 * @param pole_pairs 极对数
 * @param Ts    运行周期
 */
void FOC_VF_Init(FOC_VF_t *foc_vf, float pole_pairs, float Ts)
{
    foc_vf->Ts = Ts;
    foc_vf->speed.pole_pairs = pole_pairs;
}


/**
 * @brief VF角度计算
 * 
 * @param foc_vf 
 */
void FOC_VF_Angle_Calc(FOC_VF_t *foc_vf)
{   
    /*计算每次拖动的步态，可以q轴强拖也可以d轴强拖*/
    foc_vf->step = foc_vf->Uqd.q * foc_vf->k + foc_vf->Uqd.d * foc_vf->k;

    /*根据k值得到电角度*/
    foc_vf->speed.ElAngle = Limit_Angle(foc_vf->speed.ElAngle + foc_vf->step);
}



/**
 * @brief VF速度计算
 * 
 * @param foc_vf 
 */
void FOC_VF_Speed_Calc(FOC_VF_t *foc_vf) 
{
    float ws = foc_vf->step/foc_vf->Ts /foc_vf->speed.pole_pairs *60 /_2PI;

    if(isnan(ws) || isinf(ws)){
        return;
    }
    foc_vf->speed.AvrMecSpeed = ws;
}













