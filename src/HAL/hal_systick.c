#include "hal_systick.h"

//extern HAL_SysTickFreq CurrentSysTickFreq = ST_UNDEFINED_FREQ;
//extern HAL_SysTickSrc CurrentSysTickSource = ST_UNDEFINED_SOURCE;

void HAL_SysTick_Init(HAL_SysTick* SysTick, HAL_SysTickSrc Source, HAL_SysTickFreq Freq, HAL_SysTick_Type Type)
{
	/* Enable general interrupts */
	enableInterrupts();

    HAL_SysTick_ChangeSource(SysTick, Source);

    HAL_SysTick_ChangeFreq(SysTick, Freq);
    
    SysTick->type = Type;
}

void HAL_SysTick_Stop(HAL_SysTick* SysTick)
{
    switch (SysTick->source)
    {
    case TIMER4:
        CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, DISABLE);
        TIM4_DeInit();
        TIM4_ITConfig(TIM4_IT_Update, DISABLE);
        TIM4_Cmd(DISABLE);
        break;

    case TIMER3:
        CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, DISABLE);
        TIM3_DeInit();
        TIM3_ITConfig(TIM3_IT_Update, DISABLE);
        TIM3_Cmd(DISABLE);
        break;

    case TIMER2:
        CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, DISABLE);
        TIM2_DeInit();
        TIM2_ITConfig(TIM2_IT_Update, DISABLE);
        TIM2_Cmd(DISABLE);
        break;
    
    default:
        break;
    }

    HAL_SysTick_ChangeFreq(SysTick, ST_UNDEFINED_FREQ);
    HAL_SysTick_ChangeSource(SysTick, ST_UNDEFINED_SOURCE);
}

void HAL_SysTick_ChangeFreq(HAL_SysTick* SysTick, HAL_SysTickFreq Freq)
{
    if (SysTick->freq == Freq)
    {
        return;
    }
    else
    {
        SysTick->freq = Freq;
    }

    uint32_t SysFreq = CLK_GetClockFreq();

    uint32_t RequestedFreq = 0;

    uint8_t RequiredPrescaler = 0;
    uint8_t RequiredReload = 0;

    switch (Freq)
    {
    case SysTick_100000:
        
        RequestedFreq = 100000;
        RequiredPrescaler = TIM4_Prescaler_1;
        RequiredReload = (SysFreq >> RequiredPrescaler) / RequestedFreq;
        break;
    
    case SysTick_10000:
        
        RequestedFreq = 10000;
        RequiredPrescaler = TIM4_Prescaler_8;
        RequiredReload = (SysFreq >> RequiredPrescaler) / RequestedFreq;
        break;
    
    case SysTick_1000:
        
        RequestedFreq = 1000;
        RequiredPrescaler = TIM4_Prescaler_64;
        RequiredReload = (SysFreq >> RequiredPrescaler) / RequestedFreq;
        break;
    
    case SysTick_500:
        
        RequestedFreq = 500;
        RequiredPrescaler = TIM4_Prescaler_128;
        RequiredReload = (SysFreq >> RequiredPrescaler) / RequestedFreq;
        break;
    
    case SysTick_100:
        
        RequestedFreq = 100;
        RequiredPrescaler = TIM4_Prescaler_1024;
        RequiredReload = (SysFreq >> RequiredPrescaler) / RequestedFreq;
        break;
    
    default:
        break;
    }

    switch (SysTick->source)
    {
    case TIMER4:        
        /* Stop TIM4 */
        TIM4_Cmd(DISABLE);
        
        TIM4_TimeBaseInit(RequiredPrescaler, RequiredReload);
        TIM4_ARRPreloadConfig(ENABLE);
        TIM4_SetAutoreload(RequiredReload);
        
        /* Start TIM4 */
        TIM4_Cmd(ENABLE);
        break;
    
    case TIMER3:
        TIM3_TimeBaseInit(RequiredPrescaler, TIM3_CounterMode_Down, RequiredReload);
        TIM3_ARRPreloadConfig(ENABLE);
        TIM3_SetAutoreload(RequiredReload);
        break;
    
    case TIMER2:
        TIM2_TimeBaseInit(RequiredPrescaler, TIM2_CounterMode_Down, RequiredReload);
        TIM2_ARRPreloadConfig(ENABLE);
        TIM2_SetAutoreload(RequiredReload);
        break;
    
    default:
        break;
    }
}

void HAL_SysTick_ChangeSource(HAL_SysTick* SysTick, HAL_SysTickSrc Source)
{
    if (SysTick->source == Source)
    {
        return;
    }
    else
    {
        SysTick->source = Source;
    }
    

    switch (Source)
    {
    case TIMER4:
        CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
        TIM4_DeInit();
        TIM4_ITConfig(TIM4_IT_Update, ENABLE);
        TIM4_Cmd(DISABLE);
        break;
        
    case TIMER3:
        CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, ENABLE);
        TIM3_DeInit();
        TIM3_ITConfig(TIM3_IT_Update, ENABLE);
        TIM3_Cmd(DISABLE);
        break;
        
    case TIMER2:
        CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
        TIM2_DeInit();
        TIM2_ITConfig(TIM2_IT_Update, ENABLE);
        TIM2_Cmd(DISABLE);
        break;
    
    default:
        break;
    }
}