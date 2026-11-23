

#include "./MCAL/GPIO/GPIO.h"
#include "./MCAL/GPIO/GPIO_PRIV.h"

GPIO_enuErrCode GPIO_enuPinWrite(GPIO_PORT port, GPIO_PIN pin, GPIO_enuPinStat stat)
{
    if (port < GPIOA || port > GPIOH)
    {
        return GPIO_INVALIDPARAM;
    }
    if ((uint32_t)pin > 15)
    {
        return GPIO_INVALIDPARAM;
    }
    if (stat != LOW_ACTIVEPIN && stat != HIGH_ACTIVEPIN)
    {
        return GPIO_INVALIDPARAM;
    }
    switch (stat)
    {
    case HIGH_ACTIVEPIN:
        GPIO[port]->GPIOx_BSRR = (1UL << pin); // WRITE on BS for specific port
        break;
    case LOW_ACTIVEPIN:
        GPIO[port]->GPIOx_BSRR = (1UL << (pin + 16)); // WRITE on BR for specific port
        break;
    }

    return GPIO_OK;
}
GPIO_enuErrCode GPIO_enuPinRead(GPIO_PORT port, GPIO_PIN loc_pinNum, volatile uint32_t *loc_read)
{
    if ((uint32_t)port > GPIOH)
    {
        return GPIO_INVALIDPARAM;
    }
    if ((uint32_t)loc_pinNum > 15)
    {
        return GPIO_INVALIDPARAM;
    }
    if (loc_read == NULL)
        return GPIO_NULLPTR;
    *loc_read = (GPIO[port]->GPIOx_IDR >> loc_pinNum) & 1UL;
    return GPIO_OK;
}

GPIO_enuErrCode GPIO_enuPortWrite(GPIO_PORT port, GPIO_enuPinStat stat)
{
    if ((uint32_t)port > GPIOH)
    {
        return GPIO_INVALIDPARAM;
    }
    if (stat != LOW_ACTIVEPIN && stat != HIGH_ACTIVEPIN)
    {
        return GPIO_INVALIDPARAM;
    }
    switch (stat)
    {
    case HIGH_ACTIVEPIN:
        GPIO[port]->GPIOx_BSRR = 0xFFFFUL;
        break;
    case LOW_ACTIVEPIN:
        GPIO[port]->GPIOx_BSRR = 0xFFFF0000UL;
        break;
    default:
        return GPIO_INVALIDPARAM;
    }

    return GPIO_OK;
}

GPIO_enuErrCode GPIO_enuPortRead(GPIO_PORT port, uint32_t *loc_portRead)
{
    if ((uint32_t)port > GPIOH)
    {
        return GPIO_INVALIDPARAM;
    }
    if (loc_portRead == NULL)
        return GPIO_NULLPTR;

    *loc_portRead = GPIO[port]->GPIOx_IDR & 0x0000FFFF;
    return GPIO_OK;
}

GPIO_enuErrCode GPIO_CFGSpeed(GPIO_PORT port, GPIO_PIN pin, GPIO_enuSPEED speed)
{
    if ((uint32_t)port > GPIOH)
        return GPIO_INVALIDPARAM;
    if ((uint32_t)pin > GPIO_PIN15)
        return GPIO_INVALIDPARAM;
    if ((uint32_t)speed > VHIGH_SPEED)
        return GPIO_INVALIDPARAM;

    GPIO[port]->GPIOx_OSPEEDR &= ~(VHIGH_SPEED << (pin * 2));
    GPIO[port]->GPIOx_OSPEEDR |= (speed << (pin * 2));

    return GPIO_OK;
}

GPIO_enuErrCode GPIO_CFGPUPD(GPIO_PORT port, GPIO_PIN pin, GPIO_enuPUPD pupd)
{
    if ((uint32_t)port > GPIOH)
        return GPIO_INVALIDPARAM;
    if ((uint32_t)pin > GPIO_PIN15)
        return GPIO_INVALIDPARAM;
    if ((uint32_t)pupd > PULLDOWN)
        return GPIO_INVALIDPARAM;

    GPIO[port]->GPIOx_PUPDR &= ~(PUMASK << (pin * 2));
    GPIO[port]->GPIOx_PUPDR |= (pupd << (pin * 2));

    return GPIO_OK;
}

GPIO_enuErrCode GPIO_CFGPinMode(GPIO_PORT port, GPIO_PIN pin, GPIO_enuMODE mode)
{
    if ((uint32_t)port > GPIOH)
        return GPIO_INVALIDPARAM;
    if ((uint32_t)pin > GPIO_PIN15)
        return GPIO_INVALIDPARAM;
    if ((uint32_t)mode > MODE_ANALOG)
        return GPIO_INVALIDPARAM;

    GPIO[port]->GPIOx_MODER &= ~(MODE_ANALOG << (pin * 2));
    GPIO[port]->GPIOx_MODER |= (mode << (pin * 2));

    return GPIO_OK;
}

GPIO_enuErrCode GPIO_CFGOutType(GPIO_PORT port, GPIO_PIN pin, GPIO_enuOUTTYPE type)
{
    if ((uint32_t)port > GPIOH)
        return GPIO_INVALIDPARAM;
    if ((uint32_t)pin > GPIO_PIN15)
        return GPIO_INVALIDPARAM;
    if (type != PUSHPULL && type != OPENDRAIN)
        return GPIO_INVALIDPARAM;

    GPIO[port]->GPIOx_OTYPER &= ~(OPENDRAIN << pin);
    GPIO[port]->GPIOx_OTYPER |= (type << pin);

    return GPIO_OK;
}

GPIO_enuErrCode GPIO_enuCFGAltern(GPIO_PORT port, GPIO_PIN pin, GPIO_enuAFR alter)
{

    if ((uint32_t)port > GPIOH)
        return GPIO_INVALIDPARAM;
    if ((uint32_t)pin > GPIO_PIN15)
        return GPIO_INVALIDPARAM;
    if ((uint32_t)alter > GPIO_AFR15)
        return GPIO_INVALIDPARAM;

    switch (pin > GPIO_PIN7)
    {
    case AFRL:
        GPIO[port]->GPIOx_AFRL &= ~(alter << (pin * 4));
        GPIO[port]->GPIOx_AFRL |= (alter << (pin * 4));
        break;

    case AFRH:
        GPIO[port]->GPIOx_AFRH &= ~(alter << ((pin % 8) * 4));
        GPIO[port]->GPIOx_AFRH |= (alter << ((pin % 8) * 4));
        break;
    default:
        return GPIO_INVALIDPARAM;
    }

    return GPIO_OK;
}

GPIO_enuErrCode GPIO_InitPin(GPIO_strInit *str)
{
    if (str == NULL)
        return GPIO_NULLPTR;
    if (!GPIO_CFGOutType(str->Init_port, str->Init_pin, str->Init_outType))
        return GPIO_INVALIDPARAM;
    if (!GPIO_CFGSpeed(str->Init_port, str->Init_pin, str->Init_speed))
        return GPIO_INVALIDPARAM;
     if (!GPIO_CFGPUPD(str->Init_port, str->Init_pin, str->Init_PUPD))
        return GPIO_INVALIDPARAM;
    if (!GPIO_enuCFGAltern(str->Init_port, str->Init_pin, str->Init_AFR))
        return GPIO_INVALIDPARAM;

    if (!GPIO_CFGPinMode(str->Init_port, str->Init_pin, str->Init_mode))
        return GPIO_INVALIDPARAM;

    return GPIO_OK;
}