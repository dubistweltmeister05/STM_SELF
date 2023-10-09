/*
 * SPI_ARDUINO_COMMS.c
 *
 *  Created on: 07-Oct-2023
 *      Author: wardawg
 */


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

void Button_Init();

void delay();

int main(void)
{
	char user_data[] = "Hello world";

	//this function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	Button_Init();

	//This function is used to initialize the SPI2 peripheral parameters
	SPI2_Inits();

	SPI_SSOEConfig(SPI2,ENABLE);

	while(1){

		while(!(GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_NO_0)));

		delay();

		//enable the SPI2 peripheral
		SPI_PeripheralControl(SPI2,ENABLE);

        //first send the length information
		uint8_t datalen = strlen(user_data);
		SPI_SendData(SPI2,&datalen,1);

		//to send data
		SPI_SendData(SPI2,(uint8_t*)user_data,strlen(user_data));

		while (SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));
		//Disable the SPI2 peripheral
		SPI_PeripheralControl(SPI2,DISABLE);
	}
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

//	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14; //For the MISO
//	GPIO_Init(&SPIPins);

		SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15; //For the MOSI
		GPIO_Init(&SPIPins);

	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12; //For the NSS
	GPIO_Init(&SPIPins);
}

void SPI2_Inits(){
	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;

	SPI2handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPI_Config.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPI_Config.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV_8;
	SPI2handle.SPI_Config.SPI_BusConfig = SPI_BUSCONGID_FD;
	SPI2handle.SPI_Config.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPI_Config.SPI_SSM = SPI_SSM_DI;

	SPI_Init(&SPI2handle);
}

void Button_Init(){
	GPIO_Handle_t Button;
	Button.pGPIOx = GPIOA;
	Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&Button);

}

void delay() {
	for (int i=0;i<500000;i++);
}










