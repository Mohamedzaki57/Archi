#include "./HAL/HSWITCH/HSWITCH.h"
#include "./HAL/HSWITCH/HSWITCH_CFG.h"
#include "./MCAL/GPIO/GPIO.h"

const HSWITCH_strSwitches HSWITCH_strArr[SWITCH_nums]={
 [SWITCH_S1]={
    .port=GPIOB,
    .pin=GPIO_PIN12,
    .pupd=PULLDOWN,
    .activStat=HIGH_ACTIVEPIN

 },
 [SWITCH_S2]={
    .port=GPIOB,
    .pin=GPIO_PIN13,
    .pupd=PULLDOWN,
    .activStat=HIGH_ACTIVEPIN

 },
  [SWITCH_S3]={
    .port=GPIOB,
    .pin=GPIO_PIN14,
    .pupd=PULLDOWN,
    .activStat=HIGH_ACTIVEPIN

 }

};


//    GPIO_PORT port;
//     GPIO_PIN pin;
//     GPIO_enuPUPD pupd;
//     GPIO_enuPinStat activStat;
//     GPIO_enuPinStat curStat;
//     GPIO_enuPinStat prevStat;