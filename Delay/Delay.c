/* Includes ------------------------------------------------------------------*/
#include "Delay.h"

volatile uint32_t TimingDelay;
volatile uint32_t MillisCounter = 0;

/**
 * @brief  Decrements the TimingDelay variable.
 * @param  None
 * @retval None
 */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}

void Delay_ms(volatile uint32_t nTime)
{
	TimingDelay = nTime;

	while (TimingDelay != 0)
	{
		__NOP();
	}
}

void Delay_us(volatile uint32_t nTime)
{
	TIM3->CNT = nTime;
	TIM_Cmd(TIM3, ENABLE);
	while (TIM3->CNT > 0)
	{
	}
	TIM_Cmd(TIM3, DISABLE);
}

void IncreaseMillis(void)
{
	MillisCounter++;
}

uint32_t Millis(void)
{
	return MillisCounter;
}
void Delay_usTimerInit()	//TIM4
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_InitStruct;

	TIM_InitStruct.TIM_ClockDivision = 0;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_InitStruct.TIM_Period = 65535;
	TIM_InitStruct.TIM_Prescaler = 71;	//us
	TIM_TimeBaseInit(TIM4, &TIM_InitStruct);

	TIM_ClearFlag(TIM4, TIM_IT_Update);
	TIM_ITConfig(TIM4, TIM_FLAG_Update, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}
