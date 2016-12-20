#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"

void init_ADC(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef 		ADC_SETUP;

	// Enable ADC1 and GPIOC clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);

	//	PC0 - canal10
	//	PC1 - canal11
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//----------------------------------------------------------
	//------------------------------------------------	ADC1
	//----------------------------------------------------------
	// MODO INDEPENDIENTE
	ADC_SETUP.ADC_Mode					= ADC_Mode_Independent;
	ADC_SETUP.ADC_DataAlign  		  	= ADC_DataAlign_Right;
	// MODO CONTINUO HABILITADO
	ADC_SETUP.ADC_ContinuousConvMode 	= ENABLE;
	// SIN FLANCO DE EVENTO EXTERNO
	ADC_SETUP.ADC_ExternalTrigConv 		= ADC_ExternalTrigConv_None;
	// NUMERO DE CONVERSIONES1
	ADC_SETUP.ADC_NbrOfChannel			= 1;
	// MODO SCAN DESHABILITADO
	ADC_SETUP.ADC_ScanConvMode 			= DISABLE ;
	ADC_Init(ADC1,&ADC_SETUP);
	// ENABLED ADC
	ADC_Cmd(ADC1,ENABLE);
}

uint16_t read_ADC(ADC_TypeDef* ADCx, uint8_t channel){
	ADC_RegularChannelConfig(ADCx, channel, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}
