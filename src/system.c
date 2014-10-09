#include "system.h"

RCC_ClocksTypeDef RCC_Clocks;

void PeripheralInit(void)
{
	RccInit();
	GPIOInit();
	TimerInit();
	NvicInit();
	//Delay_usTimerInit();
}

void RccInit(void)
{
//	RCC_DeInit();

	ErrorStatus HSEStartUpStatus;

	RCC_HSEConfig(RCC_HSE_ON);										//turn on HSE
	HSEStartUpStatus = RCC_WaitForHSEStartUp();						//wait for HSE startup

	if (HSEStartUpStatus == SUCCESS)
	{
		FLASH_SetLatency(FLASH_Latency_2);
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		RCC_HCLKConfig(RCC_SYSCLK_Div1); /* HCLK = SYSCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1); /* PCLK2 = HCLK */
		RCC_PCLK1Config(RCC_HCLK_Div2);	/* PCLK1 = HCLK/2 */


#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL) && !defined (STM32F10X_CL)
		 RCC_PLLConfig (RCC_PLLSource_HSE_Div1 , RCC_PLLMul_3);		//set PLL source clock and clock multiplier; PLLCLK = 8MHz * 9 = 72 MHz
#else
		 RCC_PLLConfig (RCC_PLLSource_PREDIV1 , RCC_PLLMul_3);		//set PLL source clock and clock multiplier; PLLCLK = 8MHz * 9 = 72 MHz
#endif /* STM32F10X_CL */

		RCC_PLLCmd(ENABLE);											//turn on PLL
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}		//wait for PLL startup
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);					//SYSCLK from PLLCLK
		while (RCC_GetSYSCLKSource() != 0x08) {}					//wait for SYSCLK startup
	}
//	/* SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
#if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL) && !defined (STM32F10X_HD_VL) && !defined (STM32F10X_CL)
		  SysTick_Config(RCC_Clocks.SYSCLK_Frequency / 1000);
#else
		SysTick_Config((24000000 / 1000) - 1);//SysTick_Config(12000);
#endif /* STM32F10X_CL */

	//GPIO  RCC ENABLE
	RCC_APB2PeriphClockCmd(
			RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC
					| RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE
					| RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG | RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1, ENABLE);
}
void GPIOInit()
{
	GPIO_InitTypeDef GPIO_InitStruct;

//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
//	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}
void TimerInit()
{
//	TIM_TimeBaseInitTypeDef TIM_InitStruct;
//	//System Timer
//	TIM_InitStruct.TIM_ClockDivision = 0;
//	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_InitStruct.TIM_Period = 1000;
//	TIM_InitStruct.TIM_Prescaler = 72;
//	TIM_TimeBaseInit(TIM4, &TIM_InitStruct);
//
//	TIM_ClearFlag( TIM4, TIM_IT_Update );
//	TIM_ITConfig(TIM4, TIM_FLAG_Update, ENABLE);
//	TIM_Cmd(TIM4, ENABLE);
}
void NvicInit()
{

}
