#include "hal_sysclk.h"

static HAL_ClkFreq CurrentClkFreq = SC_UNDEFINED_FREQ;
static HAL_ClkSource CurrentClkSource = SC_UNDEFINED_SOURCE;

void HAL_SetClkSource(HAL_ClkSource ClkSource)
{
    if (CurrentClkSource == ClkSource)
    {
        return;
    }
    else
    {
        CurrentClkSource = ClkSource;
    }
    

    switch (ClkSource)
    {
    case HSI:
        CLK_LSEConfig(CLK_LSE_OFF);
        CLK_LSICmd(DISABLE);
        CLK_HSEConfig(CLK_HSE_OFF);
        CLK_HSICmd(ENABLE);
	    while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY) != SET); // Wait for internal clock start
        break;
        
    case HSE:
        CLK_LSEConfig(CLK_LSE_OFF);
        CLK_LSICmd(DISABLE);
        CLK_HSEConfig(CLK_HSE_ON);
        CLK_HSICmd(DISABLE);
	    while(CLK_GetFlagStatus(CLK_FLAG_HSERDY) != SET); // Wait for internal clock start
        break;
        
    case LSI:
        CLK_LSEConfig(CLK_LSE_OFF);
        CLK_LSICmd(ENABLE);
        CLK_HSEConfig(CLK_HSE_OFF);
        CLK_HSICmd(DISABLE);
	    while(CLK_GetFlagStatus(CLK_FLAG_LSIRDY) != SET); // Wait for internal clock start
        break;
        
    case LSE:
        CLK_LSEConfig(CLK_LSE_ON);
        CLK_LSICmd(DISABLE);
        CLK_HSEConfig(CLK_HSE_OFF);
        CLK_HSICmd(DISABLE);
	    while(CLK_GetFlagStatus(CLK_FLAG_LSERDY) != SET); // Wait for internal clock start
        break;
    
    default:
        break;
    }
}

void HAL_SetClkFreq(HAL_ClkFreq ClkFreq)
{
    if (ClkFreq == CurrentClkFreq)
    {
        return;
    }
    else
    {
        CurrentClkFreq = ClkFreq;
    }

	/* Reset clock configuration */
	CLK_DeInit();

    switch (ClkFreq)
    {
        // HSI Speeds
    case HSI_16000000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
        break;
    
    case HSI_8000000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);
        break;
    
    case HSI_4000000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_4);
        break;
    
    case HSI_2000000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);
        break;
    
    case HSI_1000000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_16);
        break;
    
    case HSI_500000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_32);
        break;
    
    case HSI_250000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_64);
        break;
    
    case HSI_125000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_128);
        break;
    
    // LSI Speeds
    case LSI_38000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
        break;
    
    case LSI_19000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);
        break;
    
    case LSI_9500:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_4);
        break;
    
    case LSI_4750:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);
        break;
    
    case LSI_2375:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_16);
        break;
    
    case LSI_1187_5:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_32);
        break;
    
    case LSI_593_75:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_64);
        break;
    
    case LSI_296_875:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_128);
        break;

    // HSE Speeds
    case HSE_16000000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
        break;
    
    case HSE_8000000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);
        break;
    
    case HSE_4000000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_4);
        break;
    
    case HSE_2000000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);
        break;
    
    case HSE_1000000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_16);
        break;
    
    case HSE_500000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_32);
        break;
    
    case HSE_250000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_64);
        break;
    
    case HSE_125000:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_128);
        break;
    
    // LSE Speeds
    case LSE_32768:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
        break;
    
    case LSE_16384:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);
        break;
    
    case LSE_8192:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_4);
        break;
    
    case LSE_4096:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);
        break;
    
    case LSE_2048:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_16);
        break;
    
    case LSE_1024:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_32);
        break;
    
    case LSE_512:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_64);
        break;
    
    case LSE_256:
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_128);
        break;
    
    default:
        break;
    }

    /* Set clock source accordingly */
    if (ClkFreq < LSI_38000)
    {
        HAL_SetClkSource(HSI);
    }
    else if (ClkFreq < HSE_16000000)
    {
        HAL_SetClkSource(LSI);
    }
    else if (ClkFreq < LSE_32768)
    {
        HAL_SetClkSource(HSE);
    }    
    else
    {
        HAL_SetClkSource(LSE);
    }
}