#include <stm32f10x.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "i2c.h"

/* This function issues a start condition and
 * transmits the slave address + R/W bit
 *
 * Parameters:
 * 		I2Cx --> the I2C peripheral e.g. I2C1
 * 		address --> the 7 bit slave address
 * 		direction --> the tranmission direction can be:
 * 						I2C_Direction_Tranmitter for Master transmitter mode
 * 						I2C_Direction_Receiver for Master receiver
 */
void I2C_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction){
	// wait until I2C1 is not busy anymore
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

	///	ENVIA CONDICION DE START
	I2C_GenerateSTART(I2Cx, ENABLE);

	// ESPERA A I2C1 EV5
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

	// ENVIA LA DIRECCION DEL ESCLAVO + LA OPERACION A REALIZAR WRITE O READ
	I2C_Send7bitAddress(I2Cx, address, direction);

	/* ESPERA A I2C1 EV6, check if
	 * either Slave has acknowledged Master transmitter or
	 * Master receiver mode, depending on the transmission
	 * direction
	 */
	if(direction == I2C_Direction_Transmitter){
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}
	else if(direction == I2C_Direction_Receiver){
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
}



/* ESTA FUNCION TRANSMITE UN DATO AL SLAVE
 * Parameters:
 *		I2Cx --> PERFIFERICO I2C
 *		data --> DATO A SER TRANSMISITIDO
 */
void I2C_write(I2C_TypeDef* I2Cx, uint8_t data){
	I2C_SendData(I2Cx, data);
	//	ESPERA A I2C1 EV8_2 --> byte has been transmitted
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

/* 	ESTA FUNCION LEE UN DATO DEL SLAVE
 * 	Y HABILITA EL BIT DE RECONOCIMIENTO
 */
uint8_t I2C_read_ack(I2C_TypeDef* I2Cx){
	//	HABILITA EL BIT DE RECONOCIMIENTO
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	// ESPERA HASTA QUE EL BYTE SE HA RECIBIDO
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	// LEE EL DATO DEL REGISTRO DE DATOS I2C
	uint8_t data = I2C_ReceiveData(I2Cx);
	return data;
}

/*	ESTA FUNCION LEE UN DATO DE UN SLAVE
 * 	Y DESHABILITA EL BIT DE RECONOCIMIENTO
 */
uint8_t I2C_read_nack(I2C_TypeDef* I2Cx){
	//	DESHABILITA EL BIT DE RECONOCIMIENTO DE DATOS
	// 	NACK Y GENERAMOS EL BIT DE STOP CUANDO EL ULTIMO DATO HA LLEGADO
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	I2C_GenerateSTOP(I2Cx, ENABLE);
	//	ESPERA HASTA QUE EL BYTE SE HA RECIBIDO
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	// LEE EL DATO DEL REGISTRO DE DATOS I2C
	uint8_t data = I2C_ReceiveData(I2Cx);
	return data;
}

/* 	ESTA FUNCION EMITE UNA CONDICION DE STOP Y POR LO TANTO
 *	LIBERA EL BUS
 */
void I2C_stop(I2C_TypeDef* I2Cx){
	//	ENVIA UNA CONDICION DE STOP
	I2C_GenerateSTOP(I2Cx, ENABLE);
}
