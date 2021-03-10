#ifndef __BEEP_H
#define __BEEP_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "common.h"
#include "delay.h"
#define GPIO_BEEP GPIOA
#define GPIO_PinSource_BEEP GPIO_PinSource8
#define GPIO_Pin_BEEP GPIO_Pin_8

#define BEEP_ON()     	 GPIOA->BSRRL = GPIO_Pin_BEEP
#define BEEP_OFF()     	 GPIOA->BSRRH = GPIO_Pin_BEEP
#define BEEP_TOGGLE() GPIO_ToggleBits(GPIO_BEEP, GPIO_Pin_BEEP)

void beepTask(void *pdata);

#ifdef __cplusplus
}
#endif

#endif