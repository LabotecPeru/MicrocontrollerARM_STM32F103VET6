#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "GPIOHYSTM32.h"

GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitTypeDef SETUP_BOTON;
GPIO_InitTypeDef SETUP_LED;

void init_LED(void){
	RCC_APB2PeriphClockCmd( CLOCK_PORTC | CLOCK_PORTD , ENABLE);
	SETUP_LED.GPIO_Pin   = D1 | D2;
	SETUP_LED.GPIO_Mode  = GPIO_Mode_Out_PP;
	SETUP_LED.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORTC, &SETUP_LED);

	SETUP_LED.GPIO_Pin = D3 | D4;
	GPIO_Init(PORTD, &SETUP_LED);
}

void outputD_HIGH(uint16_t GPIO_Pin){ GPIO_SetBits(PORTD,   GPIO_Pin); }
void outputD_LOW(uint16_t GPIO_Pin){ GPIO_ResetBits(PORTD, GPIO_Pin); }
void outputC_HIGH(uint16_t GPIO_Pin){ GPIO_SetBits(PORTC,   GPIO_Pin); }
void outputC_LOW (uint16_t GPIO_Pin){ GPIO_ResetBits(PORTC, GPIO_Pin); }

void init_BOTON(void){
	RCC_APB2PeriphClockCmd(	CLOCK_BOTON, ENABLE);
	SETUP_BOTON.GPIO_Pin   = S1|S2|S3|S4;
	SETUP_BOTON.GPIO_Mode  = GPIO_Mode_IPU;
	SETUP_BOTON.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORTE, &SETUP_BOTON);
}

int read_S1(void){	return GPIO_ReadInputDataBit(PORTE, S1); }
int read_S2(void){	return GPIO_ReadInputDataBit(PORTE, S2); }
int read_S3(void){	return GPIO_ReadInputDataBit(PORTE, S3); }
int read_S4(void){	return GPIO_ReadInputDataBit(PORTE, S4); }

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

	//	INPUT
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


}
