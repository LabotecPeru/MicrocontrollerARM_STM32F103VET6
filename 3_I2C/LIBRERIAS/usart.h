#ifndef __USART__
#define __USART__

void init_USART_IRQ(void);
void init_USART1(uint32_t baudrate);
void USART_puts(USART_TypeDef* USARTx, volatile char *s);
void putcharx(USART_TypeDef* USARTx, uint16_t Data);

#endif
