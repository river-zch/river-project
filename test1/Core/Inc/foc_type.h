#ifndef _FOC_TYPE_H
#define _FOC_TYPE_H

#include <stdint.h>


typedef struct
{
  float a;
  float b;
  float c;                      
}abc_t;

/* alphabeta 坐标系*/
typedef struct
{
  float alpha;
  float beta;
}alphabeta_t;

/*qd坐标系*/
typedef struct
{
  float q;
  float d;
} qd_t;


/*转动方向*/
typedef enum{
	REVERSAL = -1,              /*反转*/
    COROTATION = 1,             /*正转*/
}ROTATION_DIR_t;


/*速度结构体*/
typedef struct
{
    float ElAngle;              /*当前电角度*/
    float PhaseShift;           /*相位的偏移*/
    float MecAngle;             /*当前机械角度*/
    float AvrMecSpeed;          /*平均机械速度 r/min */
    float Max_MecSpeed;         /*最大机械速度限制*/
    uint32_t pole_pairs;        /*极对数*/
    ROTATION_DIR_t dir;         /*速度方向*/
}SPEED_t;





#endif

