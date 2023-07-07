/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H



#include "hal.h"



typedef enum
{
    UNDEFINED,
    INPUT,
    INPUT_ANALOG,
    INPUT_INTERRUPT,
    OUTPUT,
    OUTPUT_ANALOG,
    OUTPUT_PWM
} HAL_GPIO_Type;

typedef struct
{
    GPIO_TypeDef* port;
    GPIO_Pin_TypeDef pin;
    uint16_t value;
    HAL_GPIO_Type type;
    ADC_Channel_TypeDef ADC_Channel;
} HAL_Pin;

typedef struct HAL_PinList HAL_PinList;
struct HAL_PinList
{
    HAL_PinList* prev;
    HAL_PinList* next;

    HAL_Pin* pin;
};



extern HAL_Pin PA0;
extern HAL_Pin PA1;
extern HAL_Pin PA2;
extern HAL_Pin PA3;

extern HAL_Pin PB0;
extern HAL_Pin PB1;
extern HAL_Pin PB2;
extern HAL_Pin PB3;
extern HAL_Pin PB4;
extern HAL_Pin PB5;
extern HAL_Pin PB6;
extern HAL_Pin PB7;

extern HAL_Pin PC0;
extern HAL_Pin PC1;
extern HAL_Pin PC4;
extern HAL_Pin PC5;
extern HAL_Pin PC6;

extern HAL_Pin PD0;


extern HAL_Pin VRef;
extern HAL_Pin TempSensor;



extern HAL_Pin* PinList[20];
// extern HAL_Pin* O_ANA_Pins[18];
// extern HAL_Pin* I_ANA_Pins[18];



void HAL_GPIO_Init(void);

void HAL_GPIO_SetPinMode(HAL_Pin* pin, HAL_GPIO_Type mode);

uint16_t HAL_DigitalRead(HAL_Pin* pin);
void HAL_DigitalWrite(HAL_Pin* pin, uint16_t value);

void HAL_AddToPinList(HAL_PinList* pinToAdd, HAL_PinList* prevPin, HAL_PinList* nextPin);
void HAL_RemoveFromPinList(HAL_PinList* pinToRemove);



#endif /* __HAL_GPIO_H */