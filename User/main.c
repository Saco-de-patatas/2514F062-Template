#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "2514F062.h"
#include "2514F062_trng.h"
#include "debug.h"


void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    // PC13
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}


int main(void)
{
	union{
		uint8_t Bytes[16];
		uint32_t Words[4];
	}buffer;
	
    RCC_ClocksTypeDef clocks;
    Delay_Init();
    GPIO_Configuration();

    Delay_Init();
    USART_Cmd(USART1, DISABLE);
    USART_Printf_Init(115200);
	RCC_GetClocksFreq(&clocks);
    printf("\r\nSYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK1: %3.1fMhz, PCLK2: %3.1fMhz, ADCCLK: %3.1fMhz\r\n",
           (float)clocks.SYSCLK_Frequency / 1000000, (float)clocks.HCLK_Frequency / 1000000,
           (float)clocks.PCLK1_Frequency / 1000000, (float)clocks.PCLK2_Frequency / 1000000, 
		   (float)clocks.ADCCLK_Frequency / 1000000);
   
	TRNG_Out(ENABLE);
	TRNG_Start();
	printf("\r\nEl CheapoPill testing the True Random Number Generator at 0x50060800...\r\n");
    while (1)
    {
		
		while(TRNG_Get(buffer.Words));
		if(TRNG->RNG_INDEX&RNG_FIFO_INDEX_Mask) TRNG->RNG_INDEX=RNG_FIFO_INDEX_Mask;  //Clear possible overflow (Not important, but, anyways)
 		TRNG->RNG_CSR&=~TRNG_RNG_CSR_S128_TRNG0_Mask;								  //Start new random generation;	
			printf("SystemClk:%ld True Random Number:", SystemCoreClock);		
			for(int i=0;i<16;i++) printf(" %.2x",buffer.Bytes[i]);		
			printf("\r\n");
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        Delay_Ms(500);
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        Delay_Ms(500);
    }
}
