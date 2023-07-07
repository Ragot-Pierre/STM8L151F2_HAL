#include "hal_gpio.h"



extern HAL_Pin PA0 = {GPIOA, GPIO_Pin_0, 0, UNDEFINED, 0};
extern HAL_Pin PA1 = {GPIOA, GPIO_Pin_1, 0, UNDEFINED, 0};
extern HAL_Pin PA2 = {GPIOA, GPIO_Pin_2, 0, UNDEFINED, 0};
extern HAL_Pin PA3 = {GPIOA, GPIO_Pin_3, 0, UNDEFINED, 0};

extern HAL_Pin PB0 = {GPIOB, GPIO_Pin_0, 0, UNDEFINED, ADC_Channel_18};
extern HAL_Pin PB1 = {GPIOB, GPIO_Pin_1, 0, UNDEFINED, ADC_Channel_17};
extern HAL_Pin PB2 = {GPIOB, GPIO_Pin_2, 0, UNDEFINED, ADC_Channel_16};
extern HAL_Pin PB3 = {GPIOB, GPIO_Pin_3, 0, UNDEFINED, ADC_Channel_15};
extern HAL_Pin PB4 = {GPIOB, GPIO_Pin_4, 0, UNDEFINED, ADC_Channel_14};
extern HAL_Pin PB5 = {GPIOB, GPIO_Pin_5, 0, UNDEFINED, ADC_Channel_13};
extern HAL_Pin PB6 = {GPIOB, GPIO_Pin_6, 0, UNDEFINED, ADC_Channel_12};
extern HAL_Pin PB7 = {GPIOB, GPIO_Pin_7, 0, UNDEFINED, ADC_Channel_11};

extern HAL_Pin PC0 = {GPIOC, GPIO_Pin_0, 0, UNDEFINED, 0};
extern HAL_Pin PC1 = {GPIOC, GPIO_Pin_1, 0, UNDEFINED, 0};
extern HAL_Pin PC4 = {GPIOC, GPIO_Pin_4, 0, UNDEFINED, ADC_Channel_4};
extern HAL_Pin PC5 = {GPIOC, GPIO_Pin_5, 0, UNDEFINED, 0};
extern HAL_Pin PC6 = {GPIOC, GPIO_Pin_6, 0, UNDEFINED, 0};

extern HAL_Pin PD0 = {GPIOD, GPIO_Pin_0, 0, UNDEFINED, ADC_Channel_22};


extern HAL_Pin VRef = {0, 0, 0, INPUT_ANALOG, ADC_Channel_Vrefint};
extern HAL_Pin TempSensor = {0, 0, 0, INPUT_ANALOG, ADC_Channel_TempSensor};


extern HAL_Pin* PinList[20] = {&VRef, &TempSensor, &PA0, &PA1, &PA2, &PA3, &PB0, &PB1, &PB2, &PB3, &PB4, &PB5, &PB6, &PB7, &PC0, &PC1, &PC4, &PC5, &PC6, &PD0};
// extern HAL_Pin* O_ANA_Pins[18] = {&PA0, &PA1, &PA2, &PA3, &PB0, &PB1, &PB2, &PB3, &PB4, &PB5, &PB6, &PB7, &PC0, &PC1, &PC4, &PC5, &PC6, &PD0};
// extern HAL_Pin* I_ANA_Pins[18] = {&PA0, &PA1, &PA2, &PA3, &PB0, &PB1, &PB2, &PB3, &PB4, &PB5, &PB6, &PB7, &PC0, &PC1, &PC4, &PC5, &PC6, &PD0};



void HAL_GPIO_Init(void)
{
	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	GPIO_DeInit(GPIOD);
}

void HAL_GPIO_SetPinMode(HAL_Pin* pin, HAL_GPIO_Type mode)
{
	// if (pin->type != mode)
	// {
	// 	HAL_PinList* index = &I_ANA_Pins;

	// 	if (pin->type == OUTPUT_PWM)
	// 	{
	// 		index = &PWM_Pins;
	// 	}
	// 	else if (pin->type == OUTPUT_ANALOG)
	// 	{
	// 		index = &O_ANA_Pins;
	// 	}

	// 	do
	// 	{
	// 		if (index->pin == pin)
	// 		{
	// 			HAL_RemoveFromPinList(index);
	// 			break;
	// 		}
    //                     index = index->next;
	// 	} while (index->next != 0);
	// }
	
	pin->type = mode;

	switch (pin->type)
	{
	case UNDEFINED:
		GPIO_Init(pin->port, pin->pin, GPIO_Mode_In_FL_No_IT);
		break;
	
	case INPUT:
		GPIO_Init(pin->port, pin->pin, GPIO_Mode_In_PU_No_IT);
		break;
	
	case INPUT_ANALOG:
		GPIO_Init(pin->port, pin->pin, GPIO_Mode_In_FL_No_IT);
		// HAL_PinList* newAnaPin;
		// newAnaPin->pin = pin;
		// HAL_AddToPinList(newAnaPin, &I_ANA_Pins, I_ANA_Pins.next);
		break;
	
	case INPUT_INTERRUPT:
		GPIO_Init(pin->port, pin->pin, GPIO_Mode_In_FL_IT);
		break;
	
	case OUTPUT:
		GPIO_Init(pin->port, pin->pin, GPIO_Mode_Out_OD_Low_Fast);
		break;
	
	case OUTPUT_ANALOG:
		GPIO_Init(pin->port, pin->pin, GPIO_Mode_Out_PP_High_Fast);
		//HAL_PinList* newAnaPin = (HAL_PinList*)malloc(sizeof(HAL_PinList));
		//newAnaPin->pin = pin;
		//HAL_AddToPinList(newAnaPin, &O_ANA_Pins, O_ANA_Pins.next);
		break;
	
	case OUTPUT_PWM:
		GPIO_Init(pin->port, pin->pin, GPIO_Mode_Out_PP_High_Fast);
		//HAL_PinList* newPwmPin = (HAL_PinList*)malloc(sizeof(HAL_PinList));
		//newPwmPin->pin = pin;
		//HAL_AddToPinList(newPwmPin, &PWM_Pins, PWM_Pins.next);
		break;
	
	default:
		break;
	}
}

uint16_t HAL_DigitalRead(HAL_Pin* pin)
{
	pin->value = GPIO_ReadInputDataBit(pin->port, pin->pin);
	return pin->value;
}

void HAL_DigitalWrite(HAL_Pin* pin, uint16_t value)
{
	pin->value = value;
	if (value)
	{
		GPIO_WriteBit(pin->port, pin->pin, SET);
	}
	else
	{
		GPIO_WriteBit(pin->port, pin->pin, RESET);
	}
}

void HAL_AddToPinList(HAL_PinList* pinToAdd, HAL_PinList* prevPin, HAL_PinList* nextPin)
{
	pinToAdd->next = nextPin;
	pinToAdd->prev = prevPin;

	prevPin->next = pinToAdd;

	if (nextPin)
	{
		nextPin->prev = pinToAdd;
	}	
}

void HAL_RemoveFromPinList(HAL_PinList* pinToRemove)
{
	if (pinToRemove->next)
	{
		pinToRemove->prev->next = pinToRemove->next;
		pinToRemove->next->prev = pinToRemove->prev;
	}
	else
	{
		//pinToRemove->prev->next = NULL;
	}
	
	//free(pinToRemove);
}