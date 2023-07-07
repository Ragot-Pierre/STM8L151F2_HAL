#include "hal.h"



HAL_SysTick MainSysTick;
HAL_SysTick AnaOutSysTick;



extern void HAL_IT_SysTick(HAL_SysTickSrc Source)
{
	/* Clear Interrupt Pending bit */
	switch (Source)
	{
	case TIMER4:
		HAL_SysTick_Update = TRUE;
		TIM4_ClearITPendingBit(TIM4_IT_Update);
		break;
	
	case TIMER3:
		for (uint8_t i = 0; i < 20; i++)
		{
			if (PinList[i]->type == OUTPUT_ANALOG || PinList[i]->type == OUTPUT_PWM)
			{
				if (PinList[i]->value > HAL_SchedulerCounter)
				{
					HAL_DigitalWrite(PinList[i], 1);
				}
				else
				{
					HAL_DigitalWrite(PinList[i], 0);
				}
			}
		}

		HAL_SchedulerCounter++;

		TIM3_ClearITPendingBit(TIM3_IT_Update);
		break;
	
	case TIMER2:
		TIM2_ClearITPendingBit(TIM2_IT_Update);
		break;
	
	default:
		break;
	}
}

void main(void)
{
	/* Select system clock, both source and speed */
	HAL_SetClkFreq(HSI_16000000);
	
	/* Setup GPIO */
	HAL_GPIO_Init();

	// HAL_GPIO_SetPinMode(&PB1, OUTPUT);	
	// HAL_DigitalWrite(&PB1, 0);

	/* Setup HAL_SysTick */
	HAL_SysTick_Init(&MainSysTick, TIMER4, SysTick_1000, ST_SYSTEM);
	HAL_SysTick_Init(&AnaOutSysTick, TIMER3, SysTick_250000, ST_ANALOG_SCHEDULER);

	/* Setup HAL_ADC */
	HAL_ADC_Init();

	/*Main Loop */
	while (1)
	{
		if (HAL_SysTick_Update)
		{
			for (uint8_t i = 0; i < 20; i++)
			{
				switch (PinList[i]->type)
				{
				case OUTPUT:
					HAL_DigitalWrite(PinList[i], PinList[i]->value);
					break;
				
				case INPUT:
					PinList[i]->value = HAL_DigitalRead(PinList[i]);
					break;
				
				case INPUT_ANALOG:
					PinList[i]->value = HAL_ADC_Read(PinList[i]->ADC_Channel);
					break;
				
				default:
					break;
				}
			}

			//V_RefInt = (3.3 / 4096.0) * VRef.value;

			//Temperature = (3.3 / (0.0162 * 4096.0)) * TempSensor.value;

            HAL_SysTick_Update = FALSE;
		}
	}
}