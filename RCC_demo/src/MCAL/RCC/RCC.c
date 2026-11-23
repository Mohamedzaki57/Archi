
#include "./MCAL/RCC/RCC.h"
#include "./MCAL/RCC/BIT_MATH.h"
#include "./MCAL/RCC/RCC_Priv.h"
#include "./MCAL/RCC/RCC_CNFG.h"
///////to select clk must be ready before
RCC_errcode RCC_enuSlktSysClk(RCC_Clk clk)
{
  uint32_t loc_timeOut = TIMEOUT;
  if (!(clk == HSE || clk == HSI || clk == PLL))
  {
    return RCC_Invalidparam;
  }
  else
  {

    if ((clk == HSI)) // if hsi and ready , make it on and switch   && (RCC->CR & (1 << HSIRDY))
    {

      SetBit(RCC->CR, HSION);             // in bit math function set and on reg << by bit
      while (!(RCC->CR & (1 << HSIRDY)))
      {
        if (loc_timeOut)
        {
          loc_timeOut--;
        }
        else
        {
          return RCC_Timeout;
        }
      }
      RCC->CFGR &= ~SW_MASK;
      RCC->CFGR |= ((uint32_t)clk & SW_MASK);
      loc_timeOut = TIMEOUT;
      while ((RCC->CFGR & SWS_MASK) != (((uint32_t)clk << SWSbit) & SWS_MASK))
      {
        if (loc_timeOut)
        {
          loc_timeOut--;
        }
        else
        {
          return RCC_Timeout;
        }
      }
      return RCC_OK;
    }

  else if (clk == HSE) //&& (RCC->CR & (1 << HSERDY))
    {

      SetBit(RCC->CR, HSEON);
      loc_timeOut = TIMEOUT;
      while (!(RCC->CR & (1 << HSERDY)))
      {
        if (loc_timeOut)
        {
          loc_timeOut--;
        }
        else
        {
          return RCC_Timeout;
        }
      }
      RCC->CFGR &= ~SW_MASK;
      RCC->CFGR |= ((uint32_t)clk & SW_MASK);
      loc_timeOut = TIMEOUT;
      while ((RCC->CFGR & SWS_MASK) != (((uint32_t)HSE << SWSbit) & SWS_MASK))
      {
        if (loc_timeOut)
        {
          loc_timeOut--;
        }
        else
        {
          return RCC_Timeout;
        }
      }
      return RCC_OK;
    }

  else if (clk == PLL)
{
    if (RCC->PLLCFGR & (1U << PLLSRC))
    {
        /* PLL source is HSE */

        SetBit(RCC->CR, HSEON);

        loc_timeOut = TIMEOUT;

        while (!(RCC->CR & (1U << HSERDY)))
        {
            if (loc_timeOut == 0U)
                return RCC_Timeout;

            loc_timeOut--;
        }
    }
    else
    {
        /* PLL source is HSI */

        SetBit(RCC->CR, HSION);

        loc_timeOut = TIMEOUT;

        while (!(RCC->CR & (1U << HSIRDY)))
        {
            if (loc_timeOut == 0U)
                return RCC_Timeout;

            loc_timeOut--;
        }
    }

    /* Enable PLL */

    SetBit(RCC->CR, PLLON);

    loc_timeOut = TIMEOUT;

    while (!(RCC->CR & (1U << PLLRDY)))
    {
        if (loc_timeOut == 0U)
            return RCC_Timeout;

        loc_timeOut--;
    }

    /* Select PLL */

    RCC->CFGR &= ~SW_MASK;

    RCC->CFGR |= (((uint32_t)PLL << SWbit) & SW_MASK);

    loc_timeOut = TIMEOUT;

    while ((RCC->CFGR & SWS_MASK) !=
           (((uint32_t)PLL << SWSbit) & SWS_MASK))
    {
        if (loc_timeOut == 0U)
            return RCC_Timeout;

        loc_timeOut--;
    }

    return RCC_OK;
    }
  else
    {
      return RCC_CLKNotready;
    }
  
 }
}

RCC_errcode RCC_enuClkCtrl(RCC_Clk clk, RCC_enuClkStatus status)
{
  uint32_t loc_timeOut = TIMEOUT;
  uint32_t loc_cfgr=RCC->CFGR;
  if (!(clk == HSI || clk == HSE || clk == PLL) || !(status == CLK_ON || status == CLK_OFF))
  { 
    return RCC_Invalidparam;
  }
  else
  {

    if (status == CLK_ON)
    {
      switch (clk)
      {
      case HSI:
      {
        ((RCC->CR) |= (1 << HSION));
        while (!(RCC->CR & (1 << HSIRDY)))
        {
          if (loc_timeOut)
          {
            loc_timeOut--;
          }
          else
          {
            return RCC_Timeout;
          }
        }
        return RCC_OK;
      }
      case HSE:
      {
        ((RCC->CR) |= (1 << HSEON));
        loc_timeOut = TIMEOUT;
        while (!(RCC->CR & (1 << HSERDY)))
        {
          if (loc_timeOut)
          {
            loc_timeOut--;
          }
          else
          {
            return RCC_Timeout;
          }
        }
        return RCC_OK;
      }
      case PLL:
      {
        ((RCC->CR) |= (1 << PLLON));
        loc_timeOut = TIMEOUT;
        while (!(RCC->CR & (1 << PLLRDY)))
        {
          if (loc_timeOut)
          {
            loc_timeOut--;
          }
          else
          {
            return RCC_Timeout;
          }
        }
        return RCC_OK;
      }
      }
    }
    else if (status == CLK_OFF)
    {
      switch (clk)
      {
      case HSI:
      {
        // if (!(RCC->PLLCFGR & (1 << PLLSRC)) )
        // {
        //   RCC_enuSlktSysClk(HSE);
        //   RCC->PLLCFGR |= (1 << PLLSRC);
        // }

        if(((loc_cfgr&SWS_MASK)>>SWSbit)== HSI){return RCC_clkInUse;}
        if(!(RCC->PLLCFGR & (1U << PLLSRC)) && (RCC->CR & (1<<PLLON))){return RCC_clkInUse;} //PLL on and use it 

        (RCC->CR) &=~ (1 << HSION);
        loc_timeOut = TIMEOUT;
        while (RCC->CR & (1 << HSIRDY))
        {
          if (loc_timeOut)
          {
            loc_timeOut--;
          }
          else
          {
            return RCC_Timeout;
          }
        }
        return RCC_OK;
      }
      case HSE:
      {
        // if ((RCC->PLLCFGR & (1 << PLLSRC)) )
        // {
        //   RCC_enuSlktSysClk(HSI);
        //   RCC->PLLCFGR &= ~(1 << PLLSRC);
        // }
        if(((loc_cfgr&SWS_MASK)>>SWSbit)== HSE){return RCC_clkInUse;}
        if(RCC->PLLCFGR & (1U << PLLSRC) && (RCC->CR & (1<<PLLON))){return RCC_clkInUse;} //PLL on and use it 
        (RCC->CR) &= ~(1 << HSEON);
        loc_timeOut = TIMEOUT;
        while (RCC->CR & (1 << HSERDY))
        {
          if (loc_timeOut)
          {
            loc_timeOut--;
          }
          else
          {
            return RCC_Timeout;
          }
        }
        return RCC_OK;
      }
      case PLL:
      {
        // if (RCC->CFGR ^ ((uint32_t)clk << SWSbit & SWS_MASK))
        // {
        //   return RCC_clkInUse;
        // }
        if(((loc_cfgr&SWS_MASK)>>SWSbit)== PLL){return RCC_clkInUse;}
        if(!(RCC->PLLCFGR & (1U << PLLSRC))){return RCC_clkInUse;} //PLL on and use it 
        (RCC->CR) &= ~(1 << PLLON);
        loc_timeOut = TIMEOUT;
        while (RCC->CR & (1 << PLLRDY))
        {
          if (loc_timeOut)
          {
            loc_timeOut--;
          }
          else
          {
            return RCC_Timeout;
          }
        }
        return RCC_OK;
      }
      }
    }
  }
  return RCC_Timeout;
}

RCC_errcode RCC_enuPLL_CNFG(volatile RCC_strPll *ref_str) // we can change m,n,p,q only when the pll are disable
{

  if ((RCC->CR & (1 << PLLON)) || ref_str == NULL)
  {
    return RCC_Invalidparam;
  }

  volatile uint32_t SRC;
  volatile uint32_t VCOin;
  volatile uint32_t VCOout;
  volatile uint32_t VCOq;
  volatile uint32_t VCOp;
  volatile uint32_t loc_PLL;
  volatile uint32_t loc_P;

  switch (ref_str->PLL_clksrc)
  {
  case HSI:
    SRC = HSI_default;
    if (!(RCC->CR & (1 << HSIRDY)))
    {
      return RCC_CLKNotready;
    }
    break;

  case HSE:
    SRC = HSE_default;
    if (!(RCC->CR & (1 << HSERDY)))
    {
      return RCC_CLKNotready;
    }
    break;

  default:
    return RCC_Invalidparam;
  }

  if (ref_str->PLL_u32M > 63 || ref_str->PLL_u32M < 2)
  {
    return RCC_Invalidparam;
  }
  VCOin = SRC / ref_str->PLL_u32M;
  if ((SRC < ((uint32_t)ref_str->PLL_u32M) || SRC > 2 * ((uint32_t)ref_str->PLL_u32M) ) )
  {
    // volatile uint32_t cond1= SRC < ((uint32_t)ref_str->PLL_u32M);
    //     volatile uint32_t cond2= SRC > 2 * ((uint32_t)ref_str->PLL_u32M);
    return RCC_Invalidparam;
  }
  if (ref_str->PLL_u32N > 432 || ref_str->PLL_u32N < 192) return RCC_Invalidparam;

  VCOout = VCOin * ref_str->PLL_u32N;
  if (VCOout < 192 || VCOout > 432) return RCC_Invalidparam;

  if (ref_str->PLL_u32Q > 15 || ref_str->PLL_u32Q < 2)
  {
    return RCC_Invalidparam;
  }
  VCOq = VCOout / ref_str->PLL_u32Q;
  if (VCOq != 48UL)
  {
    return RCC_Invalidparam;
  }

  if (ref_str->PLL_u32P < 2 || ref_str->PLL_u32P > 8 || ref_str->PLL_u32P % 2)
  {

    return RCC_Invalidparam;
  }
  VCOp = VCOout / ref_str->PLL_u32P;
  if (VCOp > 84UL)
  {
    return RCC_Invalidparam;
  }
  loc_P = (ref_str->PLL_u32P / 2) - 1;
  loc_PLL = RCC->PLLCFGR;
  loc_PLL &= ~(PLL_MMask | PLL_NMask | PLL_PMask | PLL_QMask | (1 << PLLSRC));
  loc_PLL |= (ref_str->PLL_u32M << PLL_Mbit) | (ref_str->PLL_u32N << PLL_Nbit) | (ref_str->PLL_u32Q << PLL_Qbit) | (loc_P << PLL_Pbit) | ((ref_str->PLL_clksrc == HSE) ? (1UL << 22) : 0UL);
  RCC->PLLCFGR = loc_PLL;
  // RCC->CR |= (1 << PLLON);
  // while (!(RCC->CR & (1 << PLLRDY)))
  // {
  //   if (loc_timeOut)
  //   {
  //     loc_timeOut--;
  //   }
  //   else
  //   {
  //     return RCC_Timeout;
  //   }
  // }
  return RCC_OK;
}

RCC_errcode RCC_enuPeripheralCLK(RCC_periph prph, RCC_enuClkStatus stat, RCC_buses bus)
{
  if (prph < 0 || prph > 32 || stat < 0 || stat > 1 || bus < 0 || bus > 3)
  {
    return RCC_Invalidparam;
  }
  if (stat == 0)
  {
    switch (bus)
    {
    case AHB1:
      RCC->AHB1ENR |= (1UL << prph);
      break;
    case AHB2:
      RCC->AHB2ENR |= (1UL << prph);
      break;
    case APB1:
      RCC->APB1ENR |= (1UL << prph);
      break;
    case APB2:
      RCC->APB2ENR |= (1UL << prph);
      break;
    default:
    return RCC_Invalidparam;
    }
  }
  else
  { //
    switch (bus)
    {
    case AHB1:
      RCC->AHB1ENR &= ~(1UL << prph);
      break;
    case AHB2:
      RCC->AHB2ENR &= ~(1UL << prph);
      break;
    case APB1:
      RCC->APB1ENR &= ~(1UL << prph);
      break;
    case APB2:
      RCC->APB2ENR &= ~(1UL << prph);
      break;
    default:
    return RCC_Invalidparam;
    }
  }
  return RCC_OK;
}

RCC_errcode RCC_enuGetSysCLKFreq(uint32_t *f) ////
{
  if (f == NULL)
  {
    return RCC_Invalidparam;
  }

  uint32_t loc_pll;
  switch ((RCC->CFGR & SWS_MASK) >> SWSbit)
  {
  case HSE:
    *f = HSE_default;
    return RCC_OK;

  case HSI:

    *f = HSI_default;
    return RCC_OK;

  case PLL:
  {

    loc_pll = RCC->PLLCFGR;

    uint32_t m = (loc_pll & PLL_MMask) << PLL_Mbit;
    uint32_t n = (loc_pll & PLL_NMask) << PLL_Nbit;
    uint32_t p = (loc_pll & PLL_PMask) << PLL_Pbit;
    // uint32_t q = (loc_pll & PLL_QMask) << PLL_Qbit;
    RCC_Clk c = (loc_pll & (1 << PLLSRC)) ? HSE_default : HSI_default;

    uint32_t VCout = ((uint32_t)c * n) / m;
    *f = (VCout / p);

    return RCC_OK;
  }
  default:
    return RCC_Timeout;
  }
}

RCC_errcode RCC_enuGetResetCause(RCC_Resetcause *r)
{
   uint32_t loc_csr = RCC->CSR;
   if(r==NULL){return RCC_Invalidparam;}
   
  
  if (loc_csr & (1 << LPWRRSTF))
  {
    *r= LPWRRSTF;
  
  }

  if (loc_csr & (1 << WWDGRSTF))
  {
    *r = WWDGRSTF;
   
  }
  else if (loc_csr & (1 << IWDGRSTF))
  {
    *r= IWDGRSTF;
   
  }
  else if (loc_csr & (1 << SFTRSTF))
  {

    *r= SFTRSTF;
   
  }
  else if (loc_csr & (1 << PORRSTF))
  {
    *r = PORRSTF;
    
  }
  else if (loc_csr & (1 << PINRSTF))
  {
    *r = PINRSTF;
    
  }
  else if (loc_csr & (1 << BORRSTF))
  {
    *r = BORRSTF;
    
  }
     return RCC_OK;
}

RCC_errcode RCC_enuGetCLKstat(RCC_Ready_status *r)
{
  if(r==NULL){return RCC_Invalidparam;}
  uint32_t loc_cr = RCC->CR;
  if (loc_cr & (1 << PLLRDY) ||loc_cr & (1 << HSERDY) ||loc_cr & (1 << HSIRDY))
  {
    

    *r = CLK_Ready;
    return RCC_OK;
  }
  else
  {
    *r = CLK_Not_ready;
    return RCC_CLKNotready;
  }
}

RCC_errcode RCC_enuGetSysCLK(RCC_Clk *r)
{
  if(r==NULL){ return RCC_Invalidparam;}
  volatile uint32_t loc_cfgr = RCC->CFGR;



  switch ((loc_cfgr & SWS_MASK)>>SWSbit)
  {
  case HSE:
      *r=HSE;
       break;
  case HSI:
      *r=HSI;
       break;
  case PLL:
      *r= PLL;
       break;
  
  default:
    return RCC_Invalidparam;
    
  }
  return RCC_OK;
  
}

RCC_errcode RCC_enuSetPrescaler(RCC_buses bus, RCC_busPrescaler pres)
{
  if (bus < AHB1 || bus > APB2)
  {
    return RCC_Invalidparam;
  }

  switch (bus)
  {
  case AHB1:
  case AHB2:

    if (pres < notDiv || pres > div512)
    {
      return RCC_Invalidparam;
    }

    RCC->CFGR &=~(div512 << HPRE);
    RCC->CFGR |= (pres << HPRE);
    return RCC_OK;

  case APB1:
    if (pres < APB_notDiv || pres > APB_div16)
    {
      return RCC_Invalidparam;
    }

    RCC->CFGR &=~(APB_div16 << PPRE1);
    RCC->CFGR |= (pres << PPRE1);
    return RCC_OK;
  
  case APB2:
    if (pres < APB_notDiv || pres > APB_div16)
    {
      return RCC_Invalidparam;
    }

    RCC->CFGR &=~(APB_div16 << PPRE2);
    RCC->CFGR |= (pres << PPRE2);
    return RCC_OK;

  default:
   return RCC_Invalidparam;
    break;
  }
}