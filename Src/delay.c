#include "delay.h"

void delayms(uint16_t ms) {
    uint32_t ticks = ms * (OS_TICKS_PER_SEC / 1000.0f);
    OSTimeDly(ticks);
}

void delay(uint16_t sec) {
    uint32_t ticks = sec * (OS_TICKS_PER_SEC / 100.0f);
    OSTimeDly(ticks);
}