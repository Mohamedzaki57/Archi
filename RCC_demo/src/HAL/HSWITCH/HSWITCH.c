
#include "./HAL/HSWITCH/HSWITCH.h"
extern const HSWITCH_strSwitches HSWITCH_strArr[SWITCH_nums];

HSWITCH_enuErrCode HSWITCH_Init(HSWITCH_enuSwitches loc_switch )
{
    GPIO_CFGPinMode(HSWITCH_strArr[loc_switch].port, HSWITCH_strArr[loc_switch].pin, MODE_IN);
    GPIO_CFGOutType(HSWITCH_strArr[loc_switch].port, HSWITCH_strArr[loc_switch].pin, HSWITCH_strArr[loc_switch].outtype);

    GPIO_CFGSpeed(HSWITCH_strArr[loc_switch].port, HSWITCH_strArr[loc_switch].pin, HSWITCH_strArr[loc_switch].speed);

    GPIO_enuPinWrite(HSWITCH_strArr[loc_switch].port, HSWITCH_strArr[loc_switch].pin, HSWITCH_strArr[loc_switch].activestat);
}


HSWITCH_enuErrCode HSWITCH_enuReadStat(HSWITCH_strSwitRuntime curSwitch, HSWITCH_strSwitRuntime *curStat)
{

    if (curStat == NULL)
        return HSWITCH_INVALIDPARAM;

    *curStat = curSwitch.curStat;
}

HSWITCH_enuErrCode HSWITCH_enuRunnabl()
{

  
    HSWITCH_enuReadStat(loc_switch, &currStat);
    volatile uint32_t loc_uinRead = 0;
    if (GPIO_enuPinRead(curSwitch.pin, curSwitch.pin, &loc_uinRead) != GPIO_OK)
        return HSWITCh_FAILED;

    // switch (*loc_uinRead)
    // {
    // case 0:
    //     ;
    //     break;

    // case 1:

    // default:
    //     break;
    // }
}