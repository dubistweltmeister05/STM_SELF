/*
 * SPI_Tx_Testing.c
 *
 *  Created on: 07-Oct-2023
 *      Author: wardawg
 */

/*
 * This is a test build to send a string to the universe via SPI2
 * in master mode
 * MAX SCLK (21(can you do sum for me)MHz)
 * DFF = 0 (8 BIT) and then 1 (16 BIT)
 *
 *
 */

#include "stm32f407xx.h"
#include "string.h"
/*
 * Prototype for all functions to be used
 */

void SPI2_GPIOInits(void);

void SPI2_Inits();

int main(void)
{
	char user_data[] = "Hello world";

	//this function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	//This function is used to initialize the SPI2 peripheral parameters
	SPI2_Inits();

	//this makes NSS signal internally high and avoids MODF error
	SPI_SSIConfig(SPI2,ENABLE);

	//enable the SPI2 peripheral
	SPI_PeripheralControl(SPI2,ENABLE);

	//to send data
	SPI_SendData(SPI2,(uint8_t*)user_data,strlen(user_data));

	//lets confirm SPI is not busy
	while( SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG) );

	//Disable the SPI2 peripheral
	SPI_PeripheralControl(SPI2,DISABLE);

	while(1);

	return 0;

}



/*
 * User Function Implementation
 */
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













