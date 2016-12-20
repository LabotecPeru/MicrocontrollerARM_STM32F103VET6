#include <stm32f10x.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "i2c.h"
#include "mpu6050.h"

void init_mpu6050(void){

	I2C_start(I2C2, ( SLAVE_ADDRESS ) , I2C_Direction_Transmitter);
	I2C_write(I2C2, 0x6B);	//	REGISTRO Power Management 1 PWR_MGMT_1
	I2C_write(I2C2, 0x00);	//	CONFIGURACION POR DEFECTO
	I2C_stop(I2C2);
}

