#include "stm32f10x.h"
#include "usart.h"
#include "stm32f10x_gpio.h"
#include "misc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

GPIO_InitTypeDef GPIO_InitStructure;

void USART_puts(USART_TypeDef* USARTx, volatile char *s){
	while(*s){
		putcharx(USARTx, *s);
		*s++;
	}
}

void putcharx(USART_TypeDef* USARTx, uint16_t Data){
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	USART_SendData(USARTx, Data);

}

void USART1_IRQHandler(void){

	if( USART_GetITStatus(USART1, USART_IT_RXNE) ){
		char datax = USART_ReceiveData(USART1);
		putcharx(USART1, datax);
	}
}

void init_USART1(uint32_t baudrate){


	USART_InitTypeDef USART_InitStruct; // this is for the USART1 initilization

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA |
							 RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;            //	USART1 TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;            //	USART1 RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// CONFIGURACION DE LA ESTRUCTURA
	USART_InitStruct.USART_BaudRate 			= baudrate;							// the baudrate is set to the value we passed into this init function
	USART_InitStruct.USART_WordLength 			= USART_WordLength_8b;				// we want the data frame size to be 8 bits (standard)
	USART_InitStruct.USART_StopBits 			= USART_StopBits_1;					// we want 1 stop bit (standard)
	USART_InitStruct.USART_Parity 				= USART_Parity_No;					// we don't want a parity bit (standard)
	USART_InitStruct.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None; 	// we don't want flow control (standard)
	USART_InitStruct.USART_Mode 				= USART_Mode_Tx | USART_Mode_Rx; 	// we want to enable the transmitter and the receiver
	USART_Init(USART1, &USART_InitStruct);											// again all the properties are passed to the USART_Init function which takes care of all the bit setting
	USART_Cmd(USART1, ENABLE);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

}


void init_USART_IRQ(void){
  NVIC_InitTypeDef NVIC_InitStructure;

  // Configure the NVIC Preemption Priority Bits
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  // Enable the USART1 Interrupt
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}
