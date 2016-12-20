#include "stm32f10x.h"
#include "GPIOHYSTM32.h"
#include "i2c.h"
#include "mpu6050.h"
#include "usart.h"
#include "adc.h"

	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;

void init_I2C1(void){



	//	HABILITAR CLOCK I2C
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	//	HABILITAR CLOCK GPIOB
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);

	//	CONFIGURACION DE PINES
	GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF_OD;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	// CONEXION pines I2X
	//GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C1);	// SCL
	//GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C1); 	// SDA

	//	CONFIGURACION I2C
	I2C_InitStruct.I2C_ClockSpeed 			= 100000;
	I2C_InitStruct.I2C_Mode 				= I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle 			= I2C_DutyCycle_2;
	I2C_InitStruct.I2C_OwnAddress1 			= 0x00;
	I2C_InitStruct.I2C_Ack 					= I2C_Ack_Disable;
	I2C_InitStruct.I2C_AcknowledgedAddress 	= I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C2, &I2C_InitStruct);

	//	ENABLED I2C
	I2C_Cmd(I2C2, ENABLE);
}

int main(void){
	int16_t  	gxH=0,gxL=0,gyH=0,gyL=0,gzH=0,gzL=0;
	int16_t 	acelx=0,acely=0,acelz=0;
	int16_t 	TempH=0,TempL=0,TempT=0;

	SystemInit();

	init_HYSTM32F();

	init_USART1(9600);
	USART_puts(USART1, "HOLA ROBERT\r\n");
	//-------------------------------------------------------------------------
	init_I2C1();
	init_mpu6050();


 	while (1){
 		I2C_start(I2C2, SLAVE_ADDRESS, I2C_Direction_Transmitter);
 		I2C_write(I2C2, 0x3B); 	//	ESCRIBE UN BYTE EN EL SLAVE
 		I2C_stop(I2C2); 		// 	DETIENE LA TRANSMISION

 		I2C_start(I2C2, SLAVE_ADDRESS, I2C_Direction_Receiver);
 		gxH		=	I2C_read_ack(I2C2);
 		gxL		=	I2C_read_ack(I2C2);
 		gyH		=	I2C_read_ack(I2C2);
 		gyL		=	I2C_read_ack(I2C2);
 		gzH		=	I2C_read_ack(I2C2);
 		gzL		=	I2C_read_ack(I2C2);
 		TempH 	= 	I2C_read_ack(I2C2);
 		TempL 	= 	I2C_read_nack(I2C2); // nack
 		I2C_stop(I2C2);

 		acelx= (gxH<<8)+gxL; 	// ACELERACION EN EL EJE X
 		acely= (gyH<<8)+gyL; 	// ACELERACION EN EL EJE Y
 		acelz= (gzH<<8)+gzL; 	// ACELERACION EN EL EJE Z
 		TempT = ((TempH<<8)+TempL);
 		printf("x:%f-y:%f-z:%f-Temp:%f\r\n",acelx/SENS,acely/SENS,acelz/SENS,(TempT/340.0) + 36.53);

 	}
}




#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: point+++++++++++++++++++++++++++++er to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */



void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


