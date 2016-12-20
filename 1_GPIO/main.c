#include "stm32f10x.h"
#include "stm32_ub_fatfs.h"
#include "GPIOHYSTM32.h"
#include "usart.h"
#include "spi.h"
#include "systick.h"

GPIO_InitTypeDef  	GPIO_InitStructure;
SPI_InitTypeDef  	SPI_InitStructure;

void init_SPI( void );

int main(void)
{
	int x1 = 0;
	int x2 = 0;
	int x3 = 0;
	int x4 = 0;

	SystemInit();
	Delayinit();
	init_LED();
	init_BOTON();

	while(1){

		if( read_S1() == 0){	//	S1
			Delay(300);x1++;
			if( x1 == 1 ){	outputC_HIGH(D1);  }
			if( x1 == 2 ){	outputC_LOW(D1); x1=0;}
		}
		if( read_S2() == 0){	//	S2
			Delay(300);x2++;
			if( x2 == 1 ){	outputC_HIGH(D2);  }
			if( x2 == 2 ){	outputC_LOW(D2); x2=0;}
		}
		if( read_S3() == 0){	//	S3
			Delay(300);x3++;
			if( x3 == 1 ){	outputD_HIGH(D3);  }
			if( x3 == 2 ){	outputD_LOW(D3); x3=0;}
		}
		if( read_S4() == 0){	//	S4
			Delay(300);x4++;
			if( x4 == 1 ){	outputD_HIGH(D4);  }
			if( x4 == 2 ){	outputD_LOW(D4); x4=0;}
		}

	}
}

