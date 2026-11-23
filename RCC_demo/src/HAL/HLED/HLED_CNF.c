#include"./HAL/HLED/HLED_CNF.h"
#include "./HAL/HLED/HLED.h"
#include "./MCAL/GPIO/GPIO.h"

const HLED_strcfg HLED_strArr[NUMEROFLED] ={
    [firstLED]={ 
        .port=GPIOC,
        .pin=GPIO_PIN13,
        .speed=LOW_SPEED,
        .outtype=PUSHPULL,
        .activestat=LOW_ACTIVEPIN
    },
    [socendLED]={ 
        .port=GPIOC,
        .pin=GPIO_PIN14,
        .speed=HIGH_SPEED,
        .outtype=PUSHPULL,
        .activestat=LOW_ACTIVEPIN
    }
};