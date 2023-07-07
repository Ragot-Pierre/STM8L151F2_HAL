#include "hal.h"

extern bool HAL_SysTick_Update = FALSE;
extern uint8_t HAL_SchedulerCounter = 0;

//extern double V_RefInt = 0.0;
//extern double Temperature = 0.0;

void HAL_Delay_Cycles(uint32_t u32_cy)
{
	do
	{
		--u32_cy;
	}
	while(u32_cy);
}

void HAL_Delay_us(uint32_t u32_us)
{
	uint32_t u32_freq = CLK_GetClockFreq();

	uint32_t u32_cy = u32_us / (u32_freq / 2000000);

	HAL_Delay_Cycles(u32_cy);
}

void HAL_Delay_ms(uint32_t u32_ms)
{
	HAL_Delay_us(u32_ms * 1000);
}