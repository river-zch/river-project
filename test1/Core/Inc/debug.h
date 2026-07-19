#ifndef _DEBUG_TASK_H
#define _DEBUG_TASK_H
#include "usart.h"

/*vofa的通道数量*/
#define VOFA_CH_COUNT               20

#define VOFA_RECV_CH_COUNT               4

#define use_debug 0
#if use_debug
	#define debug_send(arr)   HAL_UART_Transmit(&huart3 ,(const uint8_t*)arr, sizeof(arr), 50);
#else
	#define debug_send(arr)  
#endif
/*发送结构体*/
typedef struct{
    float fdata[VOFA_CH_COUNT];
    const unsigned char tail[4];          /*尾帧 0x00, 0x00, 0x80, 0x7f*/ 
}VOFA_Send_Handle_t;

/*接收结构体*/
typedef struct{
    float fdata[VOFA_RECV_CH_COUNT];
}VOFA_Recv_Handle_t;



void Debug_Task(void);

#endif


