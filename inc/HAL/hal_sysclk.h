/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_SYSCLK_H
#define __HAL_SYSCLK_H



#include "hal.h"



typedef enum
{
    SC_UNDEFINED_SOURCE,
    HSI,
    HSE,
    LSI,
    LSE
} HAL_ClkSource;

typedef enum
{
    SC_UNDEFINED_FREQ,

    HSI_16000000,   // HSI CLK_DIV 1
    HSI_8000000,    // HSI CLK_DIV 2
    HSI_4000000,    // HSI CLK_DIV 4
    HSI_2000000,    // HSI CLK_DIV 8
    HSI_1000000,    // HSI CLK_DIV 16
    HSI_500000,     // HSI CLK_DIV 32
    HSI_250000,     // HSI CLK_DIV 64
    HSI_125000,     // HSI CLK_DIV 128

    LSI_38000,      // LSI CLK_DIV 1
    LSI_19000,      // LSI CLK_DIV 2
    LSI_9500,       // LSI CLK_DIV 4
    LSI_4750,       // LSI CLK_DIV 8
    LSI_2375,       // LSI CLK_DIV 16
    LSI_1187_5,     // LSI CLK_DIV 32
    LSI_593_75,     // LSI CLK_DIV 64
    LSI_296_875,    // LSI CLK_DIV 128

    HSE_16000000,   // HSE CLK_DIV 1
    HSE_8000000,    // HSE CLK_DIV 2
    HSE_4000000,    // HSE CLK_DIV 4
    HSE_2000000,    // HSE CLK_DIV 8
    HSE_1000000,    // HSE CLK_DIV 16
    HSE_500000,     // HSE CLK_DIV 32
    HSE_250000,     // HSI CLK_DIV 64
    HSE_125000,     // HSI CLK_DIV 128

    LSE_32768,      // LSE CLK_DIV 1
    LSE_16384,      // LSE CLK_DIV 2
    LSE_8192,       // LSE CLK_DIV 4
    LSE_4096,       // LSE CLK_DIV 8
    LSE_2048,       // LSE CLK_DIV 16
    LSE_1024,       // LSE CLK_DIV 32
    LSE_512,        // LSE CLK_DIV 64
    LSE_256         // LSE CLK_DIV 128
} HAL_ClkFreq;



static HAL_ClkFreq CurrentClkFreq;
static HAL_ClkSource CurrentClkSource;



void HAL_SetClkSource(HAL_ClkSource ClkSource);
void HAL_SetClkFreq(HAL_ClkFreq ClkFreq);



#endif /* __HAL_SYSCLK_H */