#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "GPIOHYSTM32.h"

GPIO_InitTypeDef GPIO_InitStructure;

void init_HYSTM32F(void){

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
	                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
	                         RCC_APB2Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//D1  D2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_13;	//D3, D4
	GPIO_Init(GPIOD, &GPIO_InitStructure);

}
