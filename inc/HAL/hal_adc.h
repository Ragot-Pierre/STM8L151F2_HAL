/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_ADC_H
#define __HAL_ADC_H



#include "hal.h"



void HAL_ADC_Init();

uint16_t HAL_ADC_Read(ADC_Channel_TypeDef Channel);



#endif /* __HAL_ADC_H */