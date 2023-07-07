#include "hal_adc.h"

void HAL_ADC_Init()
{
	/* Init ADC */
	CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);

	ADC_DeInit(ADC1);

	ADC_Init(ADC1, ADC_ConversionMode_Single, ADC_Resolution_12Bit, ADC_Prescaler_1);

    ADC_ExternalTrigConfig(ADC1, ADC_ExtEventSelection_None, ADC_ExtTRGSensitivity_All);

    ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_24Cycles);
    ADC_SamplingTimeConfig(ADC1, ADC_Group_FastChannels, ADC_SamplingTime_24Cycles);

    ADC_TempSensorCmd(ENABLE);
    ADC_VrefintCmd(ENABLE);

	ADC_Cmd(ADC1, ENABLE);
}

uint16_t HAL_ADC_Read(ADC_Channel_TypeDef Channel)
{
	ADC_ChannelCmd(ADC1, Channel, ENABLE);

    uint16_t tmpValue = 0;

    //HAL_Delay_Cycles(200);

    ADC_SoftwareStartConv(ADC1);

    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

    ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
    
    tmpValue = ADC_GetConversionValue(ADC1);

    ADC_ChannelCmd(ADC1, Channel, DISABLE);

    return tmpValue;
}
