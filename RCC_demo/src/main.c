#include <stdio.h>
#include <stdint.h>

#include "./MCAL/RCC/RCC.h"

#include "./MCAL/RCC/RCC_CNFG.h"
#include "./MCAL/GPIO/GPIO.h"
#include "./MCAL/STK/STK.h"

#include "./HAL/HLED/HLED_CNF.h"
#include "./HAL/HLED/HLED.h"
#include "./APP/SCHED/SCHED.h"
#include "./HAL/HSWITCH/HSWITCH.h"

void toggle(void)
{
  HLED_enucgLEDTOG(firstLED);
}
void hswi(void)
{
  HSWITCH_enuRunnabl();
}
SCHED_strRunnables hled;
SCHED_strRunnables swi;

int main(void)
{

  RCC_enuPeripheralCLK(GPIOCEN, CLK_ON, AHB1);
 RCC_enuPeripheralCLK(GPIOBEN, CLK_ON, AHB1);
 RCC_enuPeripheralCLK(GPIOAEN, CLK_ON, AHB1);
  SCHED_init();
  hled.callback = toggle;
  hled.cycle_time = 1000;
  hled.firstDelay = 2000;
  hled.priority = 0;
  hled.lastTime = 5;

  swi.callback = hswi;
  swi.cycle_time = 1000;
  swi.firstDelay = 300;
  swi.priority = 1;
  swi.lastTime = 5;
// GPIO_enuPinWrite(GPIOC,GPIO_PIN13,HIGH_ACTIVEPIN);
// HLED_enucgLEDOn(firstLED);
SCHED_registerRunnable(&hled);
SCHED_registerRunnable(&swi);

SCHED_Start();
}