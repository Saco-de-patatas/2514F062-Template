/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __2514F062_IT_H
#define __2514F062_IT_H


#include "2514F062.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#endif /* __2514F062_IT_H */
