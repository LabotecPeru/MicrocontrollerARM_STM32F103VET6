#ifndef __ADC__
#define __ADC__

void init_ADC(void);
uint16_t read_ADC(ADC_TypeDef* ADCx, uint8_t channel);

#endif
