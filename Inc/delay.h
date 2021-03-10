#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "common.h"

void delay(uint16_t sec);
void delayms(uint16_t ms);
void delayus(uint16_t us);

#ifdef __cplusplus
}
#endif

#endif