#ifndef __GPIOHYSTM32__
#define __GPIOHYSTM32__

#define PORTE			GPIOE
#define CLOCK_BOTON		RCC_APB2Periph_GPIOE
#define S1	GPIO_Pin_5
#define	S2	GPIO_Pin_4
#define	S3	GPIO_Pin_3
#define	S4	GPIO_Pin_2

#define PORTC	GPIOC
#define CLOCK_PORTC 	RCC_APB2Periph_GPIOC
#define	D1		GPIO_Pin_6
#define	D2		GPIO_Pin_7
#define PORTD	GPIOD
#define CLOCK_PORTD 	RCC_APB2Periph_GPIOD
#define	D3		GPIO_Pin_13
#define	D4		GPIO_Pin_6

void init_HYSTM32F(void);
void init_LED(void);
void init_BOTON(void);
void outputD_HIGH(uint16_t GPIO_Pin);
void outputD_LOW(uint16_t GPIO_Pin);
void outputC_HIGH(uint16_t GPIO_Pin);
void outputC_LOW (uint16_t GPIO_Pin);
int read_S1(void);
int read_S2(void);
int read_S3(void);
int read_S4(void);

#endif
