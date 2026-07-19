#include "bsp.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <tim.h>

#include "foc_app.h"



void BSP_Init(void)
{
    delay_init(170);	

    FOC_Init();

    printf("BSP_Init: OK\r\n");
}





