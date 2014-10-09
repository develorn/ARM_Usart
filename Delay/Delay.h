#ifndef __DELAY_H__
#define __DELAY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

extern volatile uint32_t TimingDelay;
extern volatile uint32_t MillisCounter;

void TimingDelay_Decrement(void);

void Delay_ms(volatile uint32_t nTime);
void Delay_us(volatile uint32_t nTime);

void IncreaseMillis(void);
uint32_t Millis(void);

void Delay_usTimerInit();	//TIM4

#ifdef __cplusplus
}
#endif

#endif /* __DELAY_H__ */
