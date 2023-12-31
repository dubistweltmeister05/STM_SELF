/*
 * main.c
 *
 *  Created on: 28-Sep-2023
 *      Author: wardawg
 */


/*
 * Include all the header files needed for main
 */
#include "main.h"
#include "stm32f4xx.h"
#include "stdio.h"
#include "string.h"

/*
 * Here, we define all the peripheral handlers
 */

GPIO_InitTypeDef led;




/*
 * Here, we write the prototypes for the functions to be defined in the file
 */
void led_init();

void SystemClock_Config_HSE(uint8_t clk_freq);

void delay();

void Error_Handler();

int main(){

	HAL_Init();

	SystemClock_Config_HSE(SYS_CLK_FREQ_120_MHZ);

	led_init();

	while (1){
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
		delay();
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
		delay();


	}
	return 0;
}

void Error_Handler(){
	while(1);
}

void led_init(){

	__HAL_RCC_GPIOD_CLK_ENABLE();


	led.Mode = GPIO_MODE_OUTPUT_PP;
	led.Pull = GPIO_NOPULL;
	led.Speed = GPIO_SPEED_FAST;
	led.Pin = GPIO_PIN_12;
	HAL_GPIO_Init(GPIOD, &led);

	led.Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOD, &led);

}

void SystemClock_Config_HSE(uint8_t clk_freq){
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	uint8_t FLatency = 0;

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_HSI ;
	osc_init.HSEState = RCC_HSE_ON;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	switch (clk_freq){
	case SYS_CLK_FREQ_50_MHZ:{
		osc_init.PLL.PLLM = 8;
		osc_init.PLL.PLLN = 100;
		osc_init.PLL.PLLP = 2;
		osc_init.PLL.PLLQ = 2;

		clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
				RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
		clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
		clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

		FLatency = FLASH_ACR_LATENCY_1WS;

		__HAL_RCC_GPIOD_CLK_ENABLE();
		led.Pin = GPIO_PIN_12;
		led.Mode = GPIO_MODE_OUTPUT_PP;
		led.Speed = GPIO_SPEED_FREQ_HIGH;
		led.Pull = GPIO_NOPULL;

		HAL_GPIO_Init(GPIOD, &led);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);
		delay();
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);

		break;
	}

	case SYS_CLK_FREQ_84_MHZ:{
		osc_init.PLL.PLLM = 8;
		osc_init.PLL.PLLN = 168;
		osc_init.PLL.PLLP = 2;
		osc_init.PLL.PLLQ = 2;


		clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
				RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
		clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
		clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

		FLatency = FLASH_ACR_LATENCY_2WS;
		__HAL_RCC_GPIOD_CLK_ENABLE();
		led.Pin = GPIO_PIN_13;
		led.Mode = GPIO_MODE_OUTPUT_PP;
		led.Speed = GPIO_SPEED_FREQ_HIGH;
		led.Pull = GPIO_NOPULL;

		HAL_GPIO_Init(GPIOD, &led);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13,GPIO_PIN_SET);
		delay();
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13,GPIO_PIN_RESET);
		break;
	}

	case SYS_CLK_FREQ_120_MHZ:{
		osc_init.PLL.PLLM = 8;
		osc_init.PLL.PLLN = 240;
		osc_init.PLL.PLLP = 2;
		osc_init.PLL.PLLQ = 2;


		clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
				RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
		clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
		clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

		FLatency = FLASH_ACR_LATENCY_3WS;
		__HAL_RCC_GPIOD_CLK_ENABLE();
		led.Pin = GPIO_PIN_14;
		led.Mode = GPIO_MODE_OUTPUT_PP;
		led.Speed = GPIO_SPEED_FREQ_HIGH;
		led.Pull = GPIO_NOPULL;

		HAL_GPIO_Init(GPIOD, &led);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14,GPIO_PIN_SET);
		delay();
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14,GPIO_PIN_RESET);
		break;
	}
	case SYS_CLK_FREQ_168_MHZ:{

		__HAL_RCC_PWR_CLK_ENABLE();
		__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

		osc_init.PLL.PLLM = 8;
		osc_init.PLL.PLLN = 336;
		osc_init.PLL.PLLP = 2;
		osc_init.PLL.PLLQ = 2;


		clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
				RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
		clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
		clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

		FLatency = FLASH_ACR_LATENCY_5WS;
		__HAL_RCC_GPIOD_CLK_ENABLE();
		led.Pin = GPIO_PIN_15;
		led.Mode = GPIO_MODE_OUTPUT_PP;
		led.Speed = GPIO_SPEED_FREQ_HIGH;
		led.Pull = GPIO_NOPULL;

		HAL_GPIO_Init(GPIOD, &led);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,GPIO_PIN_SET);
		delay();
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,GPIO_PIN_RESET);
		break;
	}
	default:
		return;
	}
	if (HAL_RCC_OscConfig(&osc_init) != HAL_OK){
		Error_Handler();
	}

	if( HAL_RCC_ClockConfig(&clk_init, FLatency) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}



void delay(){
	for (int i=0;i<500000;i++);
}
