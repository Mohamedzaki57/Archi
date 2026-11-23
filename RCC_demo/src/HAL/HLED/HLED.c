#include "./HAL/HLED/HLED.h"
#include "./HAL/HLED/HLED_CNF.h"
#include "./MCAL/GPIO/GPIO.h"
#include "./MCAL/STK/STK.h"

extern const HLED_strcfg HLED_strArr[NUMEROFLED];

// HLED_enuErrorCode HLED_INIT()
// {
//   if(!(RCC_enuPeripheralCLK()))
// }

HLED_enuErrorCode HLED_enucgLEDOn(HLED_LEDS  led){

    GPIO_CFGPinMode(HLED_strArr[led].port ,HLED_strArr[led].pin ,MODE_OUT);
    GPIO_CFGOutType(HLED_strArr[led].port ,HLED_strArr[led].pin ,HLED_strArr[led].outtype);
 
     GPIO_CFGSpeed(HLED_strArr[led].port ,HLED_strArr[led].pin ,HLED_strArr[led].speed);

 GPIO_enuPinWrite(HLED_strArr[led].port ,HLED_strArr[led].pin , HLED_strArr[led].activestat);
 return HLED_OK;
}

HLED_enuErrorCode HLED_enucgLEDOFF(HLED_LEDS  led){

    GPIO_CFGPinMode(HLED_strArr[led].port ,HLED_strArr[led].pin ,MODE_OUT);
    GPIO_CFGOutType(HLED_strArr[led].port ,HLED_strArr[led].pin ,HLED_strArr[led].outtype);
 
     GPIO_CFGSpeed(HLED_strArr[led].port ,HLED_strArr[led].pin ,HLED_strArr[led].speed);

 GPIO_enuPinWrite(HLED_strArr[led].port ,HLED_strArr[led].pin ,!(HLED_strArr[led].activestat) );

 return HLED_OK;

}

HLED_enuErrorCode HLED_enucgLEDTOG(HLED_LEDS  led){

    volatile uint32_t loc_read =0;
    GPIO_enuPinRead( HLED_strArr[led].port ,HLED_strArr[led].pin, &loc_read);
    
        GPIO_CFGPinMode(HLED_strArr[led].port ,HLED_strArr[led].pin ,MODE_OUT);
    GPIO_CFGOutType(HLED_strArr[led].port ,HLED_strArr[led].pin ,HLED_strArr[led].outtype);
 
     GPIO_CFGSpeed(HLED_strArr[led].port ,HLED_strArr[led].pin ,HLED_strArr[led].speed);

 GPIO_enuPinWrite(HLED_strArr[led].port ,HLED_strArr[led].pin ,!(loc_read) );

 return HLED_OK;
}
// HLED_enuErrorCode HLED_enuCfgLEDOFF(HLED_strcfg)

// HLED_enuErrorCode HLED_enuCfgLEDTGL(HLED_strcfg)