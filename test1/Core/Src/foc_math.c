#include "foc_math.h"


/**
 * @brief 克拉克变换
 * 
 * @param input 三相输入
 * @return alphabeta_t 返回αβ轴
 */

alphabeta_t FOC_Clarke(abc_t input)
{
    alphabeta_t output = {0};

    #if 1
    /*等幅值变换 */
    output.alpha = input.a;
    output.beta = ((input.a + 2.0f*input.b)/SQRT_3);
    #else
    /*没有进行等幅值变换*/
    output.alpha = 1.5f * input.a;
    output.beta = SQRT_3 *(0.5f*input.a + input.b);

    #endif

    return output;
}

/**
 * @brief 克拉克逆变换
 * 
 * @param input αβ轴
 * @return abc_t 返回三相
 */
abc_t FOC_Rev_Clarke(alphabeta_t input)
{
    abc_t output = {0};
/*
    Ia = Iα;
    Ib = (√3*Iβ-Iα)/2
    Ic = (-Iα-√3*Iβ)/2 
*/
    output.a = input.alpha;
    output.b = (SQRT_3*(input.beta) -input.alpha)/2.0f;
    output.c = (-input.alpha - SQRT_3*(input.beta))/2.0f;

    return output;
}


/**
 * @brief 帕克变换
 * 
 * @param input αβ轴输入
 * @param ElAngle 电角度
 * @return qd_t 返回qd轴
 */
qd_t Foc_Park(alphabeta_t input, float ElAngle)
{
    qd_t output = {0};

    float _cos = arm_cos_f32(ElAngle);
    float _sin = arm_sin_f32(ElAngle);

    output.q = _cos*input.beta -  _sin*input.alpha;
    output.d = _cos*input.alpha + _sin*input.beta;

    return output;
}

/**
 * @brief 帕克逆变换
 * 
 * @param input qd轴
 * @param ElAngle 电角度
 * @return alphabeta_t 返回αβ轴
 */
alphabeta_t FOC_Rev_Park(qd_t input, float ElAngle)
{
    alphabeta_t output = {0};

    float _cos = arm_cos_f32(ElAngle);
    float _sin = arm_sin_f32(ElAngle);

    /*派克逆变换
    Iα = Id*cosθ - Iq*sinθ
    Iβ = Iq*cosθ + Id*sinθ 我们取Id为0的情况*/
    output.alpha = _cos* input.d - _sin* input.q;
    output.beta  = _cos* input.q + _sin* input.d;

    return output;
}




/**
 * @brief 限制角度在0-2PI之间
 * 
 * @param ElAngle 输入角度
 * @return float 返回角度
 */
float Limit_Angle(float ElAngle)
{
    while(ElAngle>_2PI||ElAngle<0){
        if(ElAngle>_2PI){
            ElAngle -= _2PI;
        }else if(ElAngle<0){
            ElAngle += _2PI;
        }
    }

    return ElAngle;
}


















