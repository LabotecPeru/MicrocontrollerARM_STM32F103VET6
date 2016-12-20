#include "stm32f10x.h"
#include "GPIOHYSTM32.h"
#include "usart.h"
#include "adc.h"

int main(void){
	int16_t ADC1canal[6];

	SystemInit();

	init_HYSTM32F();
	Delayinit();
	init_USART_IRQ();
	//-------------------------------------------------------------------------
	init_USART1(9600);
	//-------------------------------------------------------------------------
	init_ADC();

	USART_puts(USART1, "LABOTEC\r\n");
 	for(;;){
 		ADC1canal[0] = read_ADC(ADC1,ADC_Channel_10);
 		ADC1canal[1] = read_ADC(ADC1,ADC_Channel_11);

 		printf("canal10:%Lu-canal11:%Lu\r\n",ADC1canal[0],ADC1canal[1]);
 		Delay(300);

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


