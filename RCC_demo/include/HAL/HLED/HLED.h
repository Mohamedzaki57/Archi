#ifndef HLED_L
#define HLED_L
#include "./MCAL/GPIO/GPIO.h"
#include "./HAL/HLED/HLED_CNF.h"

typedef struct{

GPIO_PORT port;
GPIO_PIN pin;
GPIO_enuSPEED speed;
GPIO_enuOUTTYPE outtype;
GPIO_enuPinStat activestat;
 
}HLED_strcfg;

typedef enum{
    HLED_OK,
    HLED_INVALIDPARAM,
    HLED_NULLPTR
}HLED_enuErrorCode;

HLED_enuErrorCode HLED_enucgLEDOn(HLED_LEDS  led);
HLED_enuErrorCode HLED_enucgLEDOFF(HLED_LEDS  led);
HLED_enuErrorCode HLED_enucgLEDTOG(HLED_LEDS  led);


#endif