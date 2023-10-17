/*
 * main.c
 *
 *  Created on: Sep 24, 2023
 *      Author: wardawg
 */

/*
 * 24-09-2023
 *
 * For multiple timers the start timer api calls the same MSP_INIT function
 * if they are in the the same mode of operation (PWM/IC/OC)
 *
 * UPDATE - It Works. All 4 Timers produce a PWM, perfectly
 *
 * For all timers, all the odd channels are for the RPWM
 * and all even channels are for the LPWM
 *
 * All enable pins are connected to PE7-PE14
 */


#include "main.h"
#include "stm32f4xx.h"
#include "stm32f407xx.h"
#include "stm32f407_spi_driver.h"
#include <stdio.h>
#include <string.h>

/*
 * Prototypes of all function definitions
 */
void delay(void);

void SystemClock_Config_HSE(uint8_t clk_freq);

void Error_Handler(void);

void led_init(void);

void SPI2_Inits();

void SPI2_GPIOInits();

/*
 * Handle Variables for all peripherals
 */

GPIO_InitTypeDef led;
GPIO_InitTypeDef button;
GPIO_InitTypeDef enable;



/*
 * SPACE FOR ALL CONSTANTS TO BE DECLARED IN A GLOBAL SCOPE
 */

/*
 * MAIN CODE
 */
int main (void){


	HAL_Init();

	SystemClock_Config_HSE(SYS_CLK_FREQ_50_MHZ);

	led_init();

	char user_data[1];

	//this function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	//This function is used to initialize the SPI2 peripheral parameters
	SPI2_Inits();

	//this makes NSS signal internally high and avoids MODF error
	SPI_SSIConfig(SPI2,ENABLE);

	//enable the SPI2 peripheral
	SPI_PeripheralControl(SPI2,ENABLE);

	//to send data
	SPI_ReceiveData(SPI2,(uint8_t*)user_data,1);

	if(user_data[0] == "w"){
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	}
	else {
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

	}

	//lets confirm SPI is not busy
	while( SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG) );

	//Disable the SPI2 peripheral
	SPI_PeripheralControl(SPI2,DISABLE);

	while(1);



}

/*
 * IMPLEMENTATION OF ALL USER DEFINED FUNCTIONS APART FROM THE MAIN FUNCTION
 * IN THE ORDER OF THEIR PROTOTYPES
 */
void  delay(){
	for (int i=0;i<500000;i++);
}

void button_init(void){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	button.Mode = GPIO_MODE_INPUT;
	button.Pin = GPIO_PIN_0;
	button.Pull = GPIO_NOPULL;
	button.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOA, &button);

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

void Error_Handler(){
	while(1);
}

void led_init(){
	//1. Enabling the clock for the LED GPIOS
	__HAL_RCC_GPIOD_CLK_ENABLE();

	//2. Setting the parameters of the operation
	led.Mode = GPIO_MODE_OUTPUT_PP;
	led.Pull = GPIO_NOPULL;
	led.Speed = GPIO_SPEED_FAST;

	led.Pin = GPIO_PIN_12;
	HAL_GPIO_Init(GPIOD, &led); //green

	led.Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOD, &led); //orange

	led.Pin = GPIO_PIN_14;
	HAL_GPIO_Init(GPIOD, &led); //red

	led.Pin = GPIO_PIN_15;
	HAL_GPIO_Init(GPIOD, &led); //blue
}
void SPI2_GPIOInits(void){
	GPIO_Handle_t SPIPins;
	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13; //For the SCLK
	GPIO_Init(&SPIPins);

	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14; //For the MISO
	GPIO_Init(&SPIPins);

	//	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15; //For the MOSI
	//	GPIO_Init(&SPIPins);
	//
	//	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12; //For the NSS
	//	GPIO_Init(&SPIPins);
}

void SPI2_Inits(){
	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;

	SPI2handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPI_Config.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPI_Config.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV_2;
	SPI2handle.SPI_Config.SPI_BusConfig = SPI_BUSCONGID_FD;
	SPI2handle.SPI_Config.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPI_Config.SPI_SSM = SPI_SSM_EN;

	SPI_Init(&SPI2handle);
}


