/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_H
#define __HAL_H

#include "stm8l15x.h"
#include "stm8l15x_conf.h"

#include "hal_sysclk.h"
#include "hal_systick.h"
#include "hal_gpio.h"
#include "hal_adc.h"



extern bool HAL_SysTick_Update;
extern uint8_t HAL_SchedulerCounter;

//extern double V_RefInt;
//extern double Temperature;

void HAL_Delay_Cycles(uint32_t u32_cy);
void HAL_Delay_us(uint32_t u32_us);
void HAL_Delay_ms(uint32_t u32_ms);



#endif /* __HAL_H */