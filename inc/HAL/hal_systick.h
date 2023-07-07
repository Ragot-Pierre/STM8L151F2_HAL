/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_SYSTICK_H
#define __HAL_SYSTICK_H



#include "hal.h"



typedef enum
{
    ST_SYSTEM,
    ST_ANALOG_SCHEDULER
} HAL_SysTick_Type;

typedef enum
{
    ST_UNDEFINED_SOURCE,
    TIMER2,
    TIMER3,
    TIMER4
} HAL_SysTickSrc;

typedef enum
{
    ST_UNDEFINED_FREQ,
    SysTick_250000,
    SysTick_100000,
    SysTick_10000,
    SysTick_1000,
    SysTick_500,
    SysTick_100
} HAL_SysTickFreq;

typedef struct HAL_SysTick HAL_SysTick;
struct HAL_SysTick
{
    HAL_SysTickFreq freq;
    HAL_SysTickSrc source;
    HAL_SysTick_Type type;
};



//extern HAL_SysTickFreq CurrentSysTickFreq;
//extern HAL_SysTickSrc CurrentSysTickSource;



void HAL_SysTick_Init(HAL_SysTick* SysTick, HAL_SysTickSrc Source, HAL_SysTickFreq Freq, HAL_SysTick_Type Type);

void HAL_SysTick_Stop(HAL_SysTick* SysTick);

void HAL_SysTick_ChangeFreq(HAL_SysTick* SysTick, HAL_SysTickFreq Freq);
void HAL_SysTick_ChangeSource(HAL_SysTick* SysTick, HAL_SysTickSrc Source);

extern void HAL_IT_SysTick(HAL_SysTickSrc Source);



#endif /* __HAL_SYSTICK_H */