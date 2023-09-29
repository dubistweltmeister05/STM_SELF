/*
 * it.c
 *
 *  Created on: 28-Sep-2023
 *      Author: wardawg
 */
#include"main.h"



void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
