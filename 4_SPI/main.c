#include "stm32f10x.h"
#include "stm32_ub_fatfs.h"
#include "GPIOHYSTM32.h"
#include "usart.h"
#include "spi.h"

/*
 * 	SPI2
 * 	NSS---PB12-SPI2-NSS
 * 	MISO--PB14-SPI2-MISO
 * 	MOSI--PB15-SPI2-MOSI
 * 	SCK---PB13-SPI2-SCK
 *
 */
GPIO_InitTypeDef  	GPIO_InitStructure;
SPI_InitTypeDef  	SPI_InitStructure;


void init_SPI( void );

int main(void)
{
	int x = 0;
	FIL myFile;

	SystemInit(); // Quarz Einstellungen aktivieren

	//	CONFIGURACION GPI
	//DISCOVERYinit();
	init_HYSTM32F();
	//GPIO_SetBits(GPIOC, GPIO_Pin_6);
	//GPIO_SetBits(GPIOC, GPIO_Pin_7);
	//	INI SPI
	init_SPI();

	//	CONFIGURACION MEMORIA SD
	UB_Fatfs_Init();




	while(1){
		if( x == 0){

			//	VERIFICA SI SE REALIZA LA CONFIGURACION PARA LA MEMORIA SD
				if( UB_Fatfs_CheckMedia(MMC_0) == FATFS_OK ) {
					//	MONTA FATFS
					if( UB_Fatfs_Mount(MMC_0) == FATFS_OK ) {
						//LedHIGH(AZUL);
						GPIO_ResetBits(GPIOD, GPIO_Pin_6);
						GPIO_SetBits(GPIOC, GPIO_Pin_7);
						// CREAR FILE
						if( UB_Fatfs_OpenFile(&myFile, "0:/PRU.txt", F_WR_CLEAR) == FATFS_OK ) {
							//LedHIGH(VERDE);
							x = 1;
							//GPIO_SetBits(GPIOC, GPIO_Pin_7);
							GPIO_SetBits(GPIOC, GPIO_Pin_6);
							//	ESCRITURA EN LA MEMORIA SD
							UB_Fatfs_WriteString(&myFile,"FATFS En modo SPI");
							UB_Fatfs_WriteString(&myFile,"PRUEBA");
							UB_Fatfs_WriteString(&myFile,"123");
							// CERRAR FILE
							UB_Fatfs_CloseFile(&myFile);
				    	}
						// DESMONTAR FATFS
						UB_Fatfs_UnMount(MMC_0);
				    }
				    else {
				    	//LedHIGH(ROJO);
				    	GPIO_SetBits(GPIOD, GPIO_Pin_6);
				    }
				  }

		}

	}
}

void init_SPI( void ){


  /*
  //	HABILITA CLOCK SPI2
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

  // 	HABILITA CLOCK DE GPIOB
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  //	CONFIGURACION PINES SPI
  //	PB13 -> SPI-SCK
  //	PB14 -> SPI-MISO
  //	PB15 -> SPI-MOSI
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  //	CONFIGURACION DEL ChipSelect
  //	PB12 -> ChipSelect
  GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  //	CONEXION DEL GPIO A LA FUNCION ALTERNA SPI2
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);	//	SCK
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);	//	MISO
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);	//	MOSI
*/

  	/* Enable SPI2 GPIOB clocks */
	/* Enable USART1, GPIOA, GPIOx and AFIO clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 ,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    /* Configure SPI2 pins: SCK, MISO and MOSI */
    GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* Configure PB.12 as Output push-pull, used as Flash Chip select */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* Deselect the FLASH: Chip Select high */
    //	CONFIGURACION SPI
    SPI_InitStructure.SPI_Direction 			= SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode 				= SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize 			= SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL 				= SPI_CPOL_Low;
  	SPI_InitStructure.SPI_CPHA 				= SPI_CPHA_1Edge;
  	SPI_InitStructure.SPI_NSS 				= SPI_NSS_Soft;
  	SPI_InitStructure.SPI_BaudRatePrescaler 	= SPI_BaudRatePrescaler_2;
  	SPI_InitStructure.SPI_FirstBit 			= SPI_FirstBit_MSB;
  	SPI_Init(SPI2, &SPI_InitStructure);
  	//	ENABLED SPI
  	SPI_Cmd(SPI2, ENABLE);
}



/*
int main(void){

	SystemInit();

	init_HYSTM32F();

	init_USART_IRQ();
	//-------------------------------------------------------------------------
	init_USART1(9600);

	printf("Inicio del Proyecto\r\n");

 	while (1){


 	}
}
*/



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


