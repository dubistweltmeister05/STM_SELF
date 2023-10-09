/*
 * 001LED_TOGGLE.c
 *
 *  Created on: 25-Jul-2023
 *      Author: wardawg
 */
#include "stm32f407xx.h"
//#include "stm2f407_gpio_driver.h"
void delay() {
	for (uint32_t i = 0; i < 50000; i++)
		;
}
int main(void) {
	GPIO_Handle_t GpioLED;
	GpioLED.pGPIOx = GPIOD;
	GpioLED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GpioLED);

	GpioLED.GPIO_PinConfig.GPIO_PinNumber =GPIO_PIN_NO_13;
	GPIO_Init(&GpioLED);

	GpioLED.GPIO_PinConfig.GPIO_PinNumber =GPIO_PIN_NO_14;
	GPIO_Init(&GpioLED);

	GpioLED.GPIO_PinConfig.GPIO_PinNumber =GPIO_PIN_NO_15;
	GPIO_Init(&GpioLED);

	GPIO_Handle_t Button;
	Button.pGPIOx = GPIOA;
	Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&Button);

	while (1) {

		delay();
		GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_12);
		delay();
		GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_13);
		delay();
		GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_14);
		delay();
		GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_15);
		delay();
	}
	return 0;

}
