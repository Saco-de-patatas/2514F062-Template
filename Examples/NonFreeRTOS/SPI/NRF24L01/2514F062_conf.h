#ifndef __2514F062_CONF_H
#define __2514F062_CONF_H

/* Set system clock speed in MHZ
*  It will revert to HSI mode if not defined.
*  Otherwise, will calculate the PLL multiplier (SYSCLK / HSE_VAL).
*  If the multiplier is 1, then the PLL won't be used.
*/
#define SYSCLK_HSE      HSE(128)

/* Uncomment/Comment the line below to enable/disable peripheral header file inclusion */
#include "2514F062_adc.h"
#include "2514F062_bkp.h"
#include "2514F062_can.h"
#include "2514F062_cec.h"
#include "2514F062_crc.h"
#include "2514F062_dac.h"
#include "2514F062_dbgmcu.h"
#include "2514F062_dma.h"
#include "2514F062_exti.h"
#include "2514F062_flash.h"
#include "2514F062_fsmc.h"
#include "2514F062_gpio.h"
#include "2514F062_i2c.h"
#include "2514F062_iwdg.h"
#include "2514F062_pwr.h"
#include "2514F062_rcc.h"
#include "2514F062_rtc.h"
#include "2514F062_sdio.h"
#include "2514F062_spi.h"
#include "2514F062_tim.h"
#include "2514F062_usart.h"
#include "2514F062_wwdg.h"
#include "misc.h" /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __2514F062_CONF_H */
